//
//  BehaviorManager.h
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 26.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef BehaviorManager_h
#define BehaviorManager_h

#include <stdio.h>
#include <unordered_map>
#include <deque>
#include <Thread.h>
#include <Entity.h>
#include <Behavior.h>
#include <BehaviorType.h>

class BehaviorManager: public Thread {
public:
    BehaviorManager();
    
    ~BehaviorManager();
    
    void RegisterBehavior(Behavior* behavior);
    
    template <typename behavior_type>
    void AssignBehavior(Entity* e){
        Assign(e,BehaviorType::GetIndex<behavior_type>());
    };
    
    void DeassignBehavior(Entity* e);
    
    void addToProcess(Entity* e);

private:
    void InternalThreadEntry();
    void Assign(Entity* e, unsigned int behaviorId);
    
    std::unordered_map<unsigned int, Behavior*> Behaviors;
    std::unordered_map<Entity*, Behavior*> Entityes;
    std::deque<Entity*> processQueue;

    pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
};

#endif /* BehaviorManager_h */
