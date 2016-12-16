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

#include <Context.h>

class SystemManager;
class Entity;
class Manager;
class EntityManager;

class World {
public:
    World();
    virtual ~World();
    SystemManager* getSystemManager();
    EntityManager* getEntityManager();

    void addEntity(Entity *e);
    void changeEntity(Entity *e);
    void deleteEntity(Entity *e);
    void enable(Entity *e);
    void disable(Entity *e);
//private:
    SystemManager *sm;
    EntityManager *em;    
    Context* activeContext;
    Context* visibleContext;
    std::vector<Context*> contextList;
    
    Context* createContext();
    std::unordered_set<Entity*>* getActiveEntitySet(System* system);
    std::unordered_set<Entity*>* getVisibleEntitySet(System* system);
    
    void setActiveContext(Context* context);
    void setVisibleContext(Context* context);
    
};

#endif	/* WORLD_H */

