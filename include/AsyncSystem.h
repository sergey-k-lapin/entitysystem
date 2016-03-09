//
//  AsyncSystem.h
//  gamedemo
//
//  Created by Сергей Лапин on 07.11.15.
//  Copyright © 2015 Сергей Лапин. All rights reserved.
//

#ifndef AsyncSystem_h
#define AsyncSystem_h
#include <System.h>
#include <Thread.h>

class AsyncSystem:public System, public Thread{
public:
    AsyncSystem(World *w);
    virtual ~AsyncSystem();
protected:
    void InternalThreadEntry();
    void AddEntity(Entity* e);

    pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

};

#endif /* AsyncSystem_h */
