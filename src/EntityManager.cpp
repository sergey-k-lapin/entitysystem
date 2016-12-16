/* 
 * File:   EntityManager.cpp
 * Author: slapin
 * 
 * Created on 8 июня 2015 г., 18:44
 */

#include <EntityManager.h>
#include <World.h>
#include <Entity.h>
#include <SystemManager.h>

EntityManager::EntityManager(World *w) {
    this->world = w;
    this->StartInternalThread();
}

EntityManager::~EntityManager() {
}


void EntityManager::InternalThreadEntry(){
    while (true){
        //For each changed entity
        while ( !changed.empty() ){
            Entity* e = changed.front();
            e->update();
            changed.pop_front();
        }
        pthread_mutex_lock(&my_mutex);
        pthread_cond_wait(&cond, &my_mutex);
        pthread_mutex_unlock(&my_mutex);
        
        pthread_testcancel();
    }
}

void EntityManager::addToChange(Entity* e){
    changed.push_back( e );
//  pthread_mutex_lock(&my_mutex);
    pthread_cond_signal(&cond);
//  pthread_mutex_unlock(&my_mutex);

}