/* 
 * File:   Entity.cpp
 * Author: sergeylapin
 * 
 * Created on 22 Сентябрь 2014 г., 22:14
 */


#include <Entity.h>
#include <EntityManager.h>
//#include <SystemManager.h>

int Entity::INDEX = 0;

Entity::Entity(World *world) {
    this->world = world;
	this->id = INDEX++;
	systemBits = new SystemsBitset();
	componentBits = new ComponentsBitset();
    //Create recursive mutex
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &mutexAttr);
}

Entity::~Entity() {
    delete componentBits;
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

Entity* Entity::addComponent(Component *component){
    return addComponent(component, ComponentType::getTypeFor(component));
}

Entity* Entity::addComponent(Component *component, ComponentType *type){
    int index = type->getIndex();
#ifdef ENTITY_CHANGE_AUTOLOCK
    lock();
#endif
    if (componentBits->test(index)) {
        Component* old = components[type];
        delete old;
    } else {
        componentBits->set(index);
    }
    components[type] = component;
#ifdef ENTITY_CHANGE_AUTOLOCK
    unlock();
#endif
    return this;
}

Entity* Entity::removeComponent(Component *component){
    removeComponent(component, ComponentType::getTypeFor(component));
    return this;
}

Entity * Entity::removeComponent(ComponentType* type) {
    Entity* ret = NULL;
    auto it = components.find( type );
#ifdef ENTITY_CHANGE_AUTOLOCK
    lock();
#endif
    if (it != components.end()) {
        removeComponent(it->second, it->first);
        ret = this;
    }
#ifdef ENTITY_CHANGE_AUTOLOCK
    unlock();
#endif
    return ret;
}

void Entity::addToChange() {
    world->getEntityManager()->addToChange( this );
}

Entity* Entity::removeComponent(Component* component,ComponentType* type){
    int index = type->getIndex();
    componentBits->reset(index);
    return this;
}

Component* Entity::getComponent(ComponentType *type){
    Component* ret;
#ifdef ENTITY_CHANGE_AUTOLOCK
    lock();
#endif
    ret = NULL;
    auto it = components.find(type);
    if (it != components.end()){
        ret = it->second;
    }
#ifdef ENTITY_CHANGE_AUTOLOCK
    unlock();
#endif
    return ret;
}

void Entity::update(){
#ifdef ENTITY_CHANGE_AUTOLOCK
    lock();
#endif
     world->changeEntity( this );
#ifdef ENTITY_CHANGE_AUTOLOCK
    unlock();
#endif
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
//void Entity::changedInWorld(){
//    
//}
void Entity::deleteFromWorld(){
    
}
//void Entity::enable(){
//    
//}
//void  Entity::disable(){
//    
//}
World *Entity::getWorld(){
    return world;
};
