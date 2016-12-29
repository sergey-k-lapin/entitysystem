/* 
 * File:   Entity.h
 * Author: sergeylapin
 *
 * Created on 22 Сентябрь 2014 г., 22:14
 */

#ifndef ENTITY_H
#define	ENTITY_H


#include <config.h>
#include <vector>
#include <unordered_set>
#include <ComponentType.h>
#include <World.h>
#include <assert.h>

class Component;
class ComponentType;
class World;
class ComponentManager;


class Entity {
public:
    Entity(World *world);
    virtual ~Entity();    
    int getId();
    ComponentsBitset *getComponentBits();
    SystemsBitset *getSystemBits();
    template <typename c>
    Component *getComponent(){
        return this->getComponent(ComponentType::getTypeFor<c>());
    };
    Component *getComponent(ComponentType *type);
    void addToWorld();
    void deleteFromWorld();
    World *getWorld();
    Entity* addComponent(Component *component);
    Entity* addComponent(Component *component, ComponentType *type);
    template <typename c>
    Entity* removeComponent(){
        return this->removeComponent(ComponentType::getTypeFor<c>());
    };
    Entity* removeComponent(Component *component);
    Entity* removeComponent(ComponentType* type);
    Entity* removeComponent(Component* component, ComponentType* type);
    void update();
    int lock();
    int unlock();
    void addToChange();
    ComponentsBitset *componentBits;
    std::unordered_map<ComponentType*, Component*> components;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexAttr;
    SystemsBitset *systemBits;

private:
    int id;
    static int INDEX;
    World *world;
};

#endif	/* ENTITY_H */

