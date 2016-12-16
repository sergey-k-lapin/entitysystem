//
//  ComponentManager.hpp
//  gamedemo
//
//  Created by Сергей Лапин on 22.02.16.
//  Copyright © 2016 Сергей Лапин. All rights reserved.
//

#ifndef ComponentManager_hpp
#define ComponentManager_hpp

//#include <stdio.h>
#include <Thread.h>
//#include <deque>
#include <unordered_set>
#include <bitset>
#include <Entity.h>
#include <World.h>
#include <EntityManager.h>


class World;
class Entity;
class Component;

class ComponentManager: public Thread {
public:
    ComponentManager(World *w);
    ~ComponentManager();

    void addToChange(Entity* e);
    void InternalThreadEntry();

    std::unordered_set<Entity*> changed;

    pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
private:
    World *world;
};

#endif /* ComponentManager_hpp */
