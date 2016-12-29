/* 
 * File:   Entity.cpp
 * Author: sergeylapin
 * 
 * Created on 22 Сентябрь 2014 г., 22:14
 */


#include <Entity.h>
#include <EntityManager.h>
#include <SystemManager.h>

int Entity::INDEX = 0;

Entity::Entity(World *world) {
    this->world = world;
	this->id = INDEX++;
	systemBits = new SystemsBitset();
	componentBits = new ComponentsBitset();
    changedComponentBits = new ComponentsBitset();
    
    disabledComponetBits = new ComponentsBitset();
    disabledComponetBits->set();
    
    //Create recursive mutex
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &mutexAttr);
    
	reset();
}

Entity::~Entity() {
    reset();
    delete disabledComponetBits;
    delete componentBits;
    delete changedComponentBits;
    delete systemBits;
}

Entity* Entity::disableComponent(ComponentType* type){
    disabledComponetBits->reset(type->getIndex());
    return this;
};

Entity* Entity::enableComponent(ComponentType* type){
    disabledComponetBits->set(type->getIndex());
    return this;
};


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
//    (*componentBits) = (*changedComponentBits);
    addedComponentBits.reset();
    removedComponentBits.reset();    
//    this->changed = false;
}

bool Entity::changed(){
    return (this->addedComponentBits.none() | this->removedComponentBits.none());
}

Entity* Entity::addComponent(Component *component){
    return addComponent(component, ComponentType::getTypeFor(component));
}

Entity* Entity::addComponent(Component *component, ComponentType *type){
    int index = type->getIndex();
    lock();
    if (componentBits->test(index)) {
        Component* old = components[type];
        delete old;
    } else {
        componentBits->set(index);
    }
    components[type] = component;
    unlock();
    return this;
}

Entity* Entity::addToCurrent(Component *component, ComponentType *type){ //Remove
//    components.insert(std::pair<ComponentType*, Component*>(type, component));
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
    Entity* ret = NULL;
    auto it = components.find( type );
    lock();
    if (it != components.end()) {
        removeComponent(it->second, it->first);
        ret = this;
    }
    unlock();
    return ret;
}

void Entity::addToChange() {
    world->getEntityManager()->addToChange( this );
}

Entity* Entity::removeComponent(Component* component,ComponentType* type){
//    lock();
    int index = type->getIndex();
    componentBits->reset(index);
//    unlock();
    return this;
}

Component* Entity::getComponent(ComponentType *type){
    Component* ret;
    lock();
    ret = NULL;
    auto it = components.find(type);
    if (it != components.end()){
        ret = it->second;
    }
    unlock();
    return ret;
}

void Entity::update(){ //TODO: Должно реализоваться в ComponentManager
    this->lock();
//    (*changedComponentBits) = ((*componentBits) | addedComponentBits) & (~removedComponentBits);
//    (*componentBits) = ((*componentBits) | addedComponentBits) & (~removedComponentBits);
//    this->reset();
     world->changeEntity( this );
     this->unlock();
//    for (auto it = removedComponents.begin(); it != removedComponents.end(); ++it){
////        delete *it; //TODO: object manager...
//        components.erase(components.find(*it));
//    }
//    removedComponents.clear();
}



int Entity::lock(){
    int ret = pthread_mutex_lock( &mutex );
    assert(ret != EDEADLK);
    return ret;
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
