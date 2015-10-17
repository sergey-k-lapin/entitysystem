/* 
 * File:   World.cpp
 * Author: sergeylapin
 * 
 * Created on 28 Сентябрь 2014 г., 14:25
 */

#include "World.h"
//#include "ComponentManager.h"
#include "SystemManager.h"
#include "EntityManager.h"

World::World() {
//    cm = new ComponentManager( this );
    sm = new SystemManager( this );
    em = new EntityManager( this );
}

World::~World() {
//    delete cm;
    delete sm;
    delete em;
}

//ComponentManager* World::getComponentManager(){
//    return this->cm;
//}

SystemManager* World::getSystemManager(){
    return this->sm;
};

EntityManager* World::getEntityManager(){
    return this->em;
}

void World::addEntity(Entity *e){ //Move to System Manager
    auto systemRange = sm->systemsByComponentHash.find(*e->componentBits);
    //Check for cache component vector
    if ( systemRange != sm->systemsByComponentHash.end()){
        //Component vector succesefuly found, add Entuty to systems
        for (std::vector<System*>::iterator s = systemRange->second->begin(); s != systemRange->second->end(); ++s){
            //Add entity to systems
            (*s)->AddEntity(e);
        }
    } else {
        //Create new component vector if it possible and add entity to compatible systems
        for(auto system = sm->getSystems()->begin(); system != sm->getSystems()->end(); ++system){
            //Check bits
            if ( system->second->CompatibleWithConponents( e->componentBits ) ){
                //Add entyty to system
                system->second->AddEntity(e);
                //Add system to accept list
                sm->addSystemWithComponentBits(system->second, e->componentBits);
            }
        }
    }
    //Add entity to list
}
void World::changeEntity(Entity *e){ //Move to System Manager
    std::bitset<128> enabledSystems;
    enabledSystems.reset();
    //Take a systems
    auto systemRange = sm->systemsByComponentHash.find(*e->componentBits);
    //If result is not empty
    if ( systemRange != sm->systemsByComponentHash.end()){
        //Check for compatibility
        for (auto s = systemRange->second->begin(); s != systemRange->second->end(); ++s){
            //If current system is not compatible with entity
            if (!(*s)->CompatibleWithConponents(e->changedComponentBits)){
                //Remove entity from system
                (*s)->DeleteEntity(e);
            } else {
                //Dont delete entity from system and set bit
                enabledSystems.set((*s)->id);
            };
        }
    }
    //Try to add Entity as new one
    for(auto system = sm->getSystems()->begin(); system != sm->getSystems()->end(); ++system){
        //Check bits
        if ( system->second->CompatibleWithConponents( e->changedComponentBits ) ){
            //If not present in system
            if ( !enabledSystems.test(system->second->id) ) {
                //Add entyty to system
                system->second->AddEntity(e);
            }
            //Add system to accept list
            sm->addSystemWithComponentBits(system->second, e->changedComponentBits);
        }
    }
}
void World::deleteEntity(Entity *e){
    //TODO: Implement
}
void World::enable(Entity *e){
    //TODO: Implement
}
void World::disable(Entity *e){
    //TODO: Implement
}