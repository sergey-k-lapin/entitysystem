/* 
 * File:   Entity.h
 * Author: sergeylapin
 *
 * Created on 22 Сентябрь 2014 г., 22:14
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <bitset>
#include <vector>
#include <unordered_set>
#include "ComponentType.h"
#include "World.h"

class Component;
class ComponentType;
class World;
class ComponentManager;


class Entity {
public:
    Entity();
    Entity(World *world);
    virtual ~Entity();    
    int getId();
    std::bitset<128> *getComponentBits();
    std::bitset<128> *getSystemBits();
    bool isActive();
    bool isEnabled();
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
    
    void update();
    void reset();

    std::bitset<128> *componentBits;
    std::bitset<128> *changedComponentBits;
    
    std::unordered_map<ComponentType*, Component*> components;
    std::bitset<128> addedComponentBits;
    
    std::unordered_set<ComponentType*> removedComponents; //Must be depricated
    std::bitset<128> removedComponentBits; //Must be depricated
    
    std::vector<Component*> addComponents;
    std::vector<Component*> removeComponents;
    
    bool changed;
private:
    ComponentManager *componentManager;
    int id;
    static int INDEX;
    std::bitset<128> *systemBits;
    World *world;
};

#endif	/* ENTITY_H */

