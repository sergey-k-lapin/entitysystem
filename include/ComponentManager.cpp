//
//  ComponentManager.cpp
//  gamedemo
//
//  Created by Сергей Лапин on 22.02.16.
//  Copyright © 2016 Сергей Лапин. All rights reserved.
//

#include "ComponentManager.h"
#include <iostream>
#include <typeinfo>

ComponentManager::ComponentManager(World *w){
    this->world = w;
    this->StartInternalThread();   
}

ComponentManager::~ComponentManager(){
    
}

void ComponentManager::InternalThreadEntry(){
    std::bitset<128> result;
    bool entityProcessed = false;
    while (true){
        //For each changed entity
        for ( auto it = changed.begin(); it != changed.end(); ){
            Entity *e = *it;
            entityProcessed = false;
            
            for ( auto removeIterator = e->removeComponents.begin(); removeIterator != e->removeComponents.end();) { //Process removed components
                Component *componentToRemove = *removeIterator;
                ComponentType *addComponentType = ComponentType::getTypeFor(componentToRemove);
                
            }
            
            for (auto cit = e->addComponents.begin(); cit != e->addComponents.end(); ){ //Process added components
                Component *componentToAdd = *cit;
                ComponentType *addComponentType = ComponentType::getTypeFor(componentToAdd);
                result = *e->getSystemBits() & componentToAdd->usedInSystems;
                if ( !result.any()) {
                    e->addToCurrent(componentToAdd, addComponentType);
                    e->addedComponentBits.set( addComponentType->getIndex() );
                    world->getEntityManager()->addToChange( e );
                    entityProcessed = true;
                    e->addComponents.erase(cit);
                } else {
                    cit++;
                }
            }
            if (entityProcessed) {
                changed.erase(it);
            } else {
                it++;
            }

//            Entity* e = changed.front();
//            e->update();//Должно происходить в ComonentManager и вызываться в момент добавления или удаления сущности в/из сыстемы.
//            world->changeEntity( e );
//            e->reset();
            //changed.pop_front();
        }
        pthread_mutex_lock(&my_mutex);
        pthread_cond_wait(&cond, &my_mutex);
        pthread_mutex_unlock(&my_mutex);
        
        pthread_testcancel();
    }

}

void ComponentManager::addToChange(Entity *e){
    changed.push_back( e );
    pthread_cond_signal(&cond);
}
