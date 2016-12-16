/* 
 * File:   EntityManager.h
 * Author: slapin
 *
 * Created on 8 июня 2015 г., 18:44
 */

#ifndef ENTITYMANAGER_H
#define	ENTITYMANAGER_H

#include <deque>
#include <Thread.h>

class World;
class Entity;

class EntityManager:public Thread{
public:
    EntityManager(World *w);
    virtual ~EntityManager();
    void addToChange(Entity* e);

private:
    World* world;
    std::deque<Entity*> changed;
    void InternalThreadEntry();
    pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
};

#endif	/* ENTITYMANAGER_H */

