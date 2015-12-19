//
//  AsyncSystem.cpp
//  gamedemo
//
//  Created by Сергей Лапин on 07.11.15.
//  Copyright © 2015 Сергей Лапин. All rights reserved.
//

#include <AsyncSystem.h>

AsyncSystem::AsyncSystem(World *w):System(w){
    //this->StartInternalThread();
}

AsyncSystem::~AsyncSystem(){

}

void AsyncSystem::InternalThreadEntry(){
    while(true){
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        for (auto it = entitySet.begin(); it != entitySet.end(); ++it){
            this->processEntity(*it);
        }
        this->ApplyChanges();
        if ( entitySet.empty() && added.empty() && removed.empty() ){
            pthread_mutex_lock(&my_mutex);
            pthread_cond_wait(&cond, &my_mutex);
            pthread_mutex_unlock(&my_mutex);
        }
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
    }
}

void AsyncSystem::AddEntity(Entity* e){
    added.push_back(e);
    //  pthread_mutex_lock(&my_mutex);
    pthread_cond_signal(&cond);
    //  pthread_mutex_unlock(&my_mutex);
    
}