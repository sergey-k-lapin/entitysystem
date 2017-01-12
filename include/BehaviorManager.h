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

struct EntytyProperties {
    Behavior* behavior;
    State* currentState;
};

class BehaviorManager: public Thread {
public:
    BehaviorManager();
    
    ~BehaviorManager();
    
    void RegisterBehavior(Behavior* behavior);
    
    template <typename behavior_type>
    void AssignBehavior(Entity* e){
        Assign(e, &typeid(behavior_type));
    };
    
    void DeassignBehavior(Entity* e);
    
    void addToProcess(Entity* e);
    void MakeTransition(Entity* e);
    bool MakeTransition(Entity* e, char* name);

private:
    void InternalThreadEntry();
    void Assign(Entity* e, const std::type_info *id);
    
    std::unordered_map<const std::type_info*, Behavior*> Behaviors;
    std::unordered_map<Entity*, EntytyProperties*> Entityes;
    std::deque<Entity*> transitionQueue;

    pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
};

#endif /* BehaviorManager_h */
