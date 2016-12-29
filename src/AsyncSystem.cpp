//
//  AsyncSystem.cpp
//  gamedemo
//
//  Created by Сергей Лапин on 07.11.15.
//  Copyright © 2015 Сергей Лапин. All rights reserved.
//

#include <AsyncSystem.h>

AsyncSystem::AsyncSystem(World *w):System(w){
    
}

AsyncSystem::~AsyncSystem(){

}

void AsyncSystem::InternalThreadEntry(){
    ComponentsBitset disabled;
    while(true){
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        std::unordered_set<Entity*>* currentOutEntitySet = outEntitySet;
        for (auto it = currentOutEntitySet->begin(); it != currentOutEntitySet->end();){
            Entity* e = *it;
            e->lock();
            if (this->CompatibleWithConponents(e->componentBits)){
                this->processEntity(e);
                ++it;
            } else {
                std::cout << "Remove entity " << e << " from " << this << std::endl;
                e->systemBits->reset(this->id);
                it = currentOutEntitySet->erase(it);
            }
            e->unlock();
        }
        pthread_mutex_lock(&my_mutex);
        if ( inEntitySet->empty()/* && added.empty() && removed.empty()*/ ){
            pthread_cond_wait(&cond, &my_mutex);
        }
        pthread_mutex_unlock(&my_mutex);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
    }
}

void AsyncSystem::AddEntity(Entity* e){
    pthread_mutex_lock(&my_mutex);
    System::AddEntity(e);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&my_mutex);
    
}
