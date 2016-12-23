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

class Component;
class ComponentType;
class World;
class ComponentManager;


class Entity {
public:
//    Entity();
    Entity(World *world);
    virtual ~Entity();    
    int getId();
    ComponentsBitset *getComponentBits();
    SystemsBitset *getSystemBits();
//    bool isActive();
//    bool isEnabled();
    template <typename c>
    Component *getComponent(){
        return this->getComponent(ComponentType::getTypeFor<c>());
    };
    Component *getComponent(ComponentType *type);
    void addToWorld();
    void changedInWorld();
    void deleteFromWorld();
    void enable();
    void disable();
    World *getWorld();

    Entity* addComponent(Component *component);
    Entity* addComponent(Component *component, ComponentType *type);

    Entity* addToCurrent(Component *component, ComponentType *type);
    Entity* removeFromCurrent(Component *component);

    template <typename c>
    Entity* removeComponent(){
        return this->removeComponent(ComponentType::getTypeFor<c>());
    };
    
    Entity* removeComponent(Component *component);
    Entity* removeComponent(ComponentType* type);
    Entity* removeComponent(Component* component, ComponentType* type);
    
    template <typename c>    
    Entity* disableComponent(){
        return this->disableComponent(ComponentType::getTypeFor<c>());
    };
    Entity* disableComponent(ComponentType* type);

    template <typename c>
    Entity* enableComponent(){
        return this->enableComponent(ComponentType::getTypeFor<c>());
    };
    Entity* enableComponent(ComponentType* type);
    
    void update();
    void reset();
    
    int lock();
    int unlock();
    void addToChange();
    
    bool changed();
    
    ComponentsBitset *componentBits;
    ComponentsBitset *changedComponentBits;

    ComponentsBitset *disabledComponetBits;
    
    std::unordered_map<ComponentType*, Component*> components;
    ComponentsBitset addedComponentBits;
    
    std::unordered_set<Component*> removedComponents; //Must be depricated?
    ComponentsBitset removedComponentBits; //Must be depricated?
    
    std::vector<Component*> addComponents;
    std::unordered_map<ComponentType*, Component*> removeComponents;
    
//    bool changed;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexAttr;
    SystemsBitset *systemBits;

private:
    int id;
    static int INDEX;
    World *world;
};

#endif	/* ENTITY_H */

