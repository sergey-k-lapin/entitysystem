/* 
 * File:   EntityManager.cpp
 * Author: slapin
 * 
 * Created on 8 июня 2015 г., 18:44
 */

#include "EntityManager.h"
#include "World.h"
#include "Entity.h"
#include "SystemManager.h"

EntityManager::EntityManager(World *w) {
    this->world = w;
    this->StartInternalThread();
}

EntityManager::~EntityManager() {
}


void EntityManager::InternalThreadEntry(){
    while (true){
        //For each changed entity
//        printf("Change queue size: %i\n", changed.size());
        while ( !changed.empty() ){
            Entity* e = changed.front();
//            e->lock();
            e->update();//Должно происходить в ComonentManager и вызываться в момент добавления или удаления сущности в/из сыстемы.
//            world->changeEntity( e );
//            e->reset();
//            e->unlock();
            changed.pop_front();
        }
//        printf("Change done.\n");
        pthread_mutex_lock(&my_mutex);
        pthread_cond_wait(&cond, &my_mutex);
        pthread_mutex_unlock(&my_mutex);
        
        pthread_testcancel();
    }
}

//void EntityManager::applyChanges() {
//    //For each changed entity
//    while ( !changed.empty() ){
//        Entity* e = changed.front();
//        e->update();
//        world->changeEntity( e );
//        e->reset();
//        changed.pop_front();
//    }
//    //Clear all changed entityes
//}

void EntityManager::addToChange(Entity* e){
    changed.push_back( e );
//  pthread_mutex_lock(&my_mutex);
    pthread_cond_signal(&cond);
//  pthread_mutex_unlock(&my_mutex);

}