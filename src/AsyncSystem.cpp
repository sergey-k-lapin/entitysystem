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
        std::unordered_set<Entity*>* currentOutEntitySet = outEntitySet;
        for (auto it = currentOutEntitySet->begin(); it != currentOutEntitySet->end(); ++it){
            this->processEntity(*it);
        }
        this->ApplyChanges();
        if ( inEntitySet->empty() && added.empty() && removed.empty() ){
            pthread_mutex_lock(&my_mutex);
            pthread_cond_wait(&cond, &my_mutex);
            pthread_mutex_unlock(&my_mutex);
        }
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
    }
}

void AsyncSystem::AddEntity(Entity* e){
    System::AddEntity(e);
    //  pthread_mutex_lock(&my_mutex);
    pthread_cond_signal(&cond);
    //  pthread_mutex_unlock(&my_mutex);
    
}
