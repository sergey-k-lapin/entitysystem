//
//  BehaviorManager.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 26.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include <BehaviorManager.h>

BehaviorManager::BehaviorManager(){
    this->StartInternalThread();
}

BehaviorManager::~BehaviorManager(){
    for (auto it=Behaviors.begin(); it!= Behaviors.end(); ++it){
        delete (it->second );
    }
}

void BehaviorManager::RegisterBehavior(Behavior* behavior){
    Behaviors[&typeid(*behavior)] = behavior;
};

void BehaviorManager::Assign(Entity* e, const std::type_info *id){
    Behavior* behavior = Behaviors[id];
    if (behavior != 0) {
        EntytyProperties* properties = new struct EntytyProperties();
        properties->behavior = behavior;
        properties->currentState = behavior->getDefaultState();
        Entityes[e] = properties;
    }
};

void BehaviorManager::MakeTransition(Entity* e){
#ifdef ENTITY_CHANGE_AUTOLOCK
    e->lock();
#endif
    EntytyProperties* properties = Entityes[e];
    State* result = properties->currentState->change(e);
    if (result) {
        properties->currentState = result;
    }
#ifdef ENTITY_CHANGE_AUTOLOCK
    e->unlock();
#endif
};

bool BehaviorManager::MakeTransition(Entity* e, char* name){
    bool transitionResult = false;
#ifdef ENTITY_CHANGE_AUTOLOCK
    e->lock();
#endif
    EntytyProperties* properties = Entityes[e];
    State* newState = properties->behavior->getState(name); //Current state
    if (newState) {
        Transition* transition = properties->currentState->child[newState];
        if (transition != 0){ //Link to state exists
            transitionResult = transition->make(e); //Make transition to new state
            properties->currentState = newState; //Set new state as current
        }
    }
#ifdef ENTITY_CHANGE_AUTOLOCK
    e->unlock();
#endif
    return transitionResult;
};


void BehaviorManager::DeassignBehavior(Entity* e){
    auto it = Entityes.find(e);
    if (it != Entityes.end()){
        Entityes.erase(it);
    }
};

void BehaviorManager::addToProcess(Entity* e){
    transitionQueue.push_back( e );
    //  pthread_mutex_lock(&my_mutex);
    pthread_cond_signal(&cond);
    //  pthread_mutex_unlock(&my_mutex);

};


void BehaviorManager::InternalThreadEntry(){
    while (true){
        //For each queued entity
        while ( !transitionQueue.empty() ){
            Entity* e = transitionQueue.front();
            MakeTransition(e);
            transitionQueue.pop_front();
        }

    pthread_mutex_lock(&my_mutex);
    pthread_cond_wait(&cond, &my_mutex);
    pthread_mutex_unlock(&my_mutex);
    
    pthread_testcancel();
    }
}