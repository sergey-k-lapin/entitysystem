/* 
 * File:   Entity.cpp
 * Author: sergeylapin
 * 
 * Created on 22 Сентябрь 2014 г., 22:14
 */


#include "Entity.h"
#include "EntityManager.h"
#include "SystemManager.h"

int Entity::INDEX = 0;

//Entity::Entity() {
//    systemBits = new std::bitset<128>();
//    changed = false;    
//}

Entity::Entity(World *world) {
    this->world = world;
	this->id = INDEX++;
	systemBits = new SystemsBitset();
	componentBits = new ComponentsBitset();
    changedComponentBits = new ComponentsBitset();
    
    //Create recursive mutex
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &mutexAttr);
    
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

ComponentsBitset *Entity::getComponentBits(){
    return componentBits;
}

SystemsBitset *Entity::getSystemBits(){
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
//    lock(); //Lock while changing entity
    //To be sure that we don't have this type of component
    if ( !addedComponentBits.test(type->getIndex()) && !componentBits->test(type->getIndex()) ) {
        addedComponentBits.set(type->getIndex()); //Set as added
//        unlock(); //Unlock entity
        components.insert(std::pair<ComponentType*, Component*>(type, component)); //Add component
        //Move this block to Component constructor!
        auto it = this->world->sm->SystemsForComponent.find(type); //Find System bits for component type
        if (it == this->world->sm->SystemsForComponent.end()){ //If not found
            std::cout << "Warning: Systems for component type "<< type->index << " not found." << std::endl;
        } else {
//            std::cout << "component "<< type->getIndex() <<" use in systems " << *it->second << std::endl;
            component->usedInSystems = *it->second;
        }
//        world->getEntityManager()->addToChange( this ); //Add Entity to change queue
        return this;
    } else if (removedComponentBits.test(type->getIndex())) { //If mark as removeed, replace with new.
        components[type] = component; //Replace;
        removedComponentBits.reset( type->getIndex());
        removedComponents.erase(removedComponents.find(component));
//        unlock(); //Unlock entity
        return this;
    } else {
        return NULL;
    }
    
//    addComponents.push_back(component);
//    world->getComponentManager()->addToChange( this );
    
//    addedComponentBits.set( type->getIndex() ); //Move to ComponenManager all below
//    if (!changed){
//        world->getEntityManager()->addToChange( this );
//    }
//    changed = true;
//    return this;
}

Entity* Entity::addToCurrent(Component *component, ComponentType *type){ //Remove
    components.insert(std::pair<ComponentType*, Component*>(type, component));
    return this;
}

Entity* Entity::removeFromCurrent(Component *component){ //Remove
    ComponentType *type = ComponentType::getTypeFor(component);
    auto c = components.find(type);
    if (c != components.end()){
        components.erase(c);
        delete component;
    }
    return this;
}

Entity* Entity::removeComponent(Component *component){
    removeComponent(component, ComponentType::getTypeFor(component));
    return this;
}

Entity * Entity::removeComponent(ComponentType* type) {
    auto it = components.find( type );
    if (it != components.end()) {
        removeComponent(it->second, it->first);
        return this;
    }
    return NULL;
}

void Entity::addToChange() {
    world->getEntityManager()->addToChange( this );
}

Entity* Entity::removeComponent(Component* component,ComponentType* type){
//    lock();
    if ( componentBits->test(type->getIndex())) {
        removedComponentBits.set( type->getIndex());
//        removedComponents.insert( type );
        removedComponents.insert( component );
//        unlock();
        return this;
    } else {
        
//        unlock();
        return NULL;
    }
//    removeComponents.insert(std::pair<ComponentType*, Component*>(type, component));
//    removedComponentBits.set( type->getIndex());
//    this->world->getComponentManager()->addToChange( this );
//     world->getEntityManager()->addToChange( this );

 //    removedComponents.insert( type );
//    if (!changed){
//        world->getEntityManager()->addToChange( this );
//    }
//    changed = true;
//    return this;
}

Component* Entity::getComponent(ComponentType *type){
    auto it = components.find(type);
    if (it != components.end()){
        return it->second;
    }
    return NULL;
}

void Entity::update(){ //TODO: Должно реализоваться в ComponentManager
    this->lock();
    (*changedComponentBits) = ((*componentBits) | addedComponentBits) & (~removedComponentBits);
     world->changeEntity( this );
     this->reset();
     this->unlock();    
//    for (auto it = removedComponents.begin(); it != removedComponents.end(); ++it){
////        delete *it; //TODO: object manager...
//        components.erase(components.find(*it));
//    }
//    removedComponents.clear();
}

int Entity::lock(){
    return pthread_mutex_lock( &mutex );
}

int Entity::unlock(){
    return pthread_mutex_unlock( &mutex );
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
