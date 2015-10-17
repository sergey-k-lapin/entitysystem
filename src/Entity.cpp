/* 
 * File:   Entity.cpp
 * Author: sergeylapin
 * 
 * Created on 22 Сентябрь 2014 г., 22:14
 */

#include <unordered_set>

#include "Entity.h"
#include "EntityManager.h"

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
    components.insert(std::pair<ComponentType*, Component*>(type, component));
    addedComponentBits.set( type->getIndex() );
    if (!changed){
        world->getEntityManager()->addToChange( this );
    }
    changed = true;
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

void Entity::update(){
    (*changedComponentBits) = ((*componentBits) | addedComponentBits) & (~removedComponentBits);
    for (auto it = removedComponents.begin(); it != removedComponents.end(); ++it){
        delete *it; //TODO: object manager...
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
