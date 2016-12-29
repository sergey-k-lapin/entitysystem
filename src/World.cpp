/* 
 * File:   World.cpp
 * Author: sergeylapin
 * 
 * Created on 28 Сентябрь 2014 г., 14:25
 */

#include <World.h>
#include <SystemManager.h>
#include <EntityManager.h>
#include <BehaviorManager.h>

World::World() {
    sm = new SystemManager( this );
    em = new EntityManager( this );
    bm = new BehaviorManager();
    
    this->activeContext = new Context();
    this->visibleContext = this->activeContext;
    this->contextList.push_back(this->activeContext);
}

World::~World() {
    delete sm;
    delete em;
    delete bm;
}

SystemManager* World::getSystemManager(){
    return this->sm;
};

EntityManager* World::getEntityManager(){
    return this->em;
}

void World::addEntity(Entity *e){
    //??
}
void World::changeEntity(Entity *e){ //Move to System Manager
    ComponentsBitset  resultComponentBits = *e->componentBits;
    //Try to fing existing set
    auto systemRange = sm->systemsByComponentHash.find(resultComponentBits);
    //if exists
    if ( systemRange != sm->systemsByComponentHash.end()){
//        for(auto system = sm->getSystems()->begin(); system != sm->getSystems()->end(); ++system){
        for (auto s = systemRange->second->begin(); s != systemRange->second->end(); ++s){
            //Check bits
            if ( (*s)->CompatibleWithConponents( &resultComponentBits ) ){
                //If not present in system
                if ( !e->systemBits->test((*s)->id) ) {
                    (*s)->AddEntity(e);
                }
            }
        }
    } else {
        //Try to add Entity as new one and build new set
        for(auto system = sm->getSystems()->begin(); system != sm->getSystems()->end(); ++system){
            //Check bits
            if ( system->second->CompatibleWithConponents( &resultComponentBits ) ){
                //If not present in system
                if ( !e->systemBits->test(system->second->id) ) {
                    //Add entyty to system
                    system->second->AddEntity(e);
                }
                sm->addSystemWithComponentBits(system->second, &resultComponentBits);
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
    this->contextList.push_back(ret); //Do we realy need this?
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