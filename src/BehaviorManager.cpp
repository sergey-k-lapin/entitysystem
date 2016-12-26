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
    
}

void BehaviorManager::RegisterBehavior(Behavior* behavior){
    unsigned int BehaviorId = BehaviorType::GetIndex(behavior);
    std::cout << typeid(*behavior).name() << std::endl;
    Behaviors[BehaviorId] = behavior;
};

void BehaviorManager::Assign(Entity* e, unsigned int behaviorId){
    Behavior* behavior = Behaviors[behaviorId];
    if (behavior != 0) {
        Entityes[e] = behavior;
    }
};

void BehaviorManager::DeassignBehavior(Entity* e){
    auto it = Entityes.find(e);
    if (it != Entityes.end()){
        Entityes.erase(it);
    }
};

void BehaviorManager::addToProcess(Entity* e){
    processQueue.push_back( e );
    //  pthread_mutex_lock(&my_mutex);
    pthread_cond_signal(&cond);
    //  pthread_mutex_unlock(&my_mutex);

};


void BehaviorManager::InternalThreadEntry(){
    while (true){
        //For each changed entity
        while ( !processQueue.empty() ){
            Entity* e = processQueue.front();
            e->lock();
            Behavior* behavior = Entityes[e];
            std::cout << "Try to change behavior " << behavior << " fot entity " << e << std::endl;
            e->unlock();
            
            processQueue.pop_front();
        }

    pthread_mutex_lock(&my_mutex);
    pthread_cond_wait(&cond, &my_mutex);
    pthread_mutex_unlock(&my_mutex);
    
    pthread_testcancel();
    }
}