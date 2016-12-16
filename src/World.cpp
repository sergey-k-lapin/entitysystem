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
    this->activeContext = new Context();
    this->visibleContext = this->activeContext;
    this->contextList.push_back(this->activeContext);
//    cm = new ComponentManager( this );
}

World::~World() {
//    delete cm;
    delete sm;
    delete em;
}

//ComponentManager* World::getComponentManager(){
////    return this->cm;
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
//    std::cout << "Component bits " << *e->componentBits << std::endl;
//    std::cout << "Changed component bits " << *e->changedComponentBits << std::endl;
    //If result is not empty
    if ( systemRange != sm->systemsByComponentHash.end()){
//        std::cout << "Size of system vector " << systemRange->second->size() << " for component bits " << *e->componentBits << std::endl;
        //Check for compatibility
        for (auto s = systemRange->second->begin(); s != systemRange->second->end(); ++s){
            //If current system is not compatible with entity
            if (!(*s)->CompatibleWithConponents(e->changedComponentBits)){
                //Remove entity from system
                std::cout << "Remove from system: " << (*s) << " with ID " << (*s)->id << std::endl;
                (*s)->DeleteEntity(e);
            } else {
                //Dont delete entity from system and set bit
                enabledSystems.set((*s)->id);
            };
        }
    }
    //Try to fing existing set
    systemRange = sm->systemsByComponentHash.find(*e->changedComponentBits);
    //if exists
    if ( systemRange != sm->systemsByComponentHash.end()){
        for(auto system = sm->getSystems()->begin(); system != sm->getSystems()->end(); ++system){
            //Check bits
            if ( system->second->CompatibleWithConponents( e->changedComponentBits ) ){
                //If not present in system
                if ( !enabledSystems.test(system->second->id) ) {
                    //Add entyty to system
                    system->second->AddEntity(e);
                }
            }
        }
    } else {
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
//                std::cout << "Add entity with component bits " << *e->changedComponentBits << " to system " << system->second->id << std::endl;
                sm->addSystemWithComponentBits(system->second, e->changedComponentBits);
            }
        }
    }
}
std::unordered_set<Entity*>* World::getActiveEntitySet(System* system){
    return this->activeContext->values.find(system)->second;
}
std::unordered_set<Entity*>* World::getVisibleEntitySet(System* system){
    return this->visibleContext->values.find(system)->second;    
};

Context* World::createContext(){
    Context* ret = new Context();
    for (auto it = this->sm->systems.begin(); it != this->sm->systems.end(); ++it ){
        std::unordered_set<Entity*>* dataset = new std::unordered_set<Entity*>();
        ret->values.insert(std::pair<System*, std::unordered_set<Entity*>*>( it->second, dataset ));        
    }
    this->contextList.push_back(ret); //Не уверен нужен ли этот список вообще
    return ret;
}

void World::setActiveContext(Context* context){
    this->activeContext = context;
    for (auto it = this->sm->systems.begin(); it != this->sm->systems.end(); ++it ){
        it->second->UpdateInContext();        
    }    
};

void World::setVisibleContext(Context* context){
    this->visibleContext = context;
    for (auto it = this->sm->systems.begin(); it != this->sm->systems.end(); ++it ){
        it->second->UpdateOutContext();        
    }    
};


void World::deleteEntity(Entity *e){
    //TODO: Implement
}
void World::enable(Entity *e){
    //TODO: Implement
}
void World::disable(Entity *e){
    //TODO: Implement
}