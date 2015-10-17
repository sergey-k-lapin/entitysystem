/* 
 * File:   World.h
 * Author: sergeylapin
 *
 * Created on 28 Сентябрь 2014 г., 14:25
 */

#ifndef WORLD_H
#define	WORLD_H

#include <vector>
#include <unordered_map>

class SystemManager;
class Entity;
class Manager;
class EntityManager;

class World {
public:
    World();
    virtual ~World();
//    ComponentManager* getComponentManager();
    SystemManager* getSystemManager();
    EntityManager* getEntityManager();

    void addEntity(Entity *e);
    void changeEntity(Entity *e);
    void deleteEntity(Entity *e);
    void enable(Entity *e);
    void disable(Entity *e);
private:
    SystemManager *sm; 
    EntityManager *em;
};

#endif	/* WORLD_H */

