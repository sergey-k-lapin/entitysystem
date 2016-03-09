/* 
 * File:   Entity.cpp
 * Author: sergeylapin
 * 
 * Created on 22 Сентябрь 2014 г., 22:14
 */

#include <unordered_set>

#include "Entity.h"
#include "EntityManager.h"
#include "SystemManager.h"

int Entity::INDEX = 0;

Entity::Entity() {
    systemBits = new std::bitset<128>();
    changed = false;    
}

Entity::Entity(World *world) {
        this->world = world;
	this->id = INDEX++;
	systemBits = new std::bitset<128>(); //TODO: Remove.
	componentBits = new std::bitset<128>();
        changedComponentBits = new std::bitset<128>();
	reset();
}

Entity::~Entity() {
    reset();
    delete componentBits;
    delete changedComponentBits;
    delete systemBits;
}

int Entity::getId() {
        return this->id;
}

std::bitset<128>* Entity::getComponentBits(){
    return componentBits;
}

std::bitset<128> *Entity::getSystemBits(){
    return this->systemBits;
}

void Entity::reset(){
    //Flip bits
    (*componentBits) = (*changedComponentBits);
    addedComponentBits.reset();
    removedComponentBits.reset();    
    this->changed = false;
}

Entity* Entity::addComponent(Component *component){
    addComponent(component, ComponentType::getTypeFor(component));
    return this;
}

Entity* Entity::addComponent(Component *component, ComponentType *type){
    //addToCurrent(component, type); //Remove
    
    auto it = this->world->sm->SystemsForComponent.find(type); //Find System bits for component type
    if (it == this->world->sm->SystemsForComponent.end()){ //If not found
        std::cout << "Warning: Systems for component type "<< type->index << " not found." << std::endl;
    } else {
        component->usedInSystems = *it->second;
//        std::cout << component->usedInSystems << std::endl;
//        std::cout << *it->second << std::endl;
    }
    
    addComponents.push_back(component);
    world->getComponentManager()->addToChange( this );
    
//    addedComponentBits.set( type->getIndex() ); //Move to ComponenManager all below
//    if (!changed){
//        world->getEntityManager()->addToChange( this );
//    }
    changed = true;
    return this;
}

Entity* Entity::addToCurrent(Component *component, ComponentType *type){
    components.insert(std::pair<ComponentType*, Component*>(type, component));
    return this;
}

Entity* Entity::removeFromCurrent(Component *component){
    ComponentType *type = ComponentType::getTypeFor(component);
    auto c = components.find(type);
    if (c != components.end()){
        components.erase(c);
    }
    return this;
}

Entity* Entity::removeComponent(Component *component){
    removeComponent(ComponentType::getTypeFor(component));
    return this;
}

Entity* Entity::removeComponent(ComponentType* type){
    removedComponents.insert( type );
    removedComponentBits.set( type->getIndex());
    if (!changed){
        world->getEntityManager()->addToChange( this );
    }
    changed = true;
    return this;
}

Component* Entity::getComponent(ComponentType *type){
    auto it = components.find(type);
    if (it != components.end()){
        return it->second;
    }
    return NULL;
}

void Entity::update(){ //TODO: Должно реализоваться в ComponentManager
    (*changedComponentBits) = ((*componentBits) | addedComponentBits) & (~removedComponentBits);
    for (auto it = removedComponents.begin(); it != removedComponents.end(); ++it){
//        delete *it; //TODO: object manager...
        components.erase(components.find(*it));
    }
    removedComponents.clear();
}

void Entity::addToWorld(){
    world->addEntity(this);
}
void Entity::changedInWorld(){
    
}
void Entity::deleteFromWorld(){
    
}
void Entity::enable(){
    
}
void  Entity::disable(){
    
}
World *Entity::getWorld(){
    return world;
};
