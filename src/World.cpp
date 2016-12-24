/* 
 * File:   World.cpp
 * Author: sergeylapin
 * 
 * Created on 28 Сентябрь 2014 г., 14:25
 */

#include <World.h>
#include <SystemManager.h>
#include <EntityManager.h>

World::World() {
    sm = new SystemManager( this );
    em = new EntityManager( this );
    this->activeContext = new Context();
    this->visibleContext = this->activeContext;
    this->contextList.push_back(this->activeContext);
}

World::~World() {
    delete sm;
    delete em;
}

SystemManager* World::getSystemManager(){
    return this->sm;
};

EntityManager* World::getEntityManager(){
    return this->em;
}

void World::addEntity(Entity *e){ //DEPRICATED!
//    auto systemRange = sm->systemsByComponentHash.find(*e->componentBits);
//    //Check for cache component vector
//    if ( systemRange != sm->systemsByComponentHash.end()){
//        //Component vector succesefuly found, add Entuty to systems
//        for (std::vector<System*>::iterator s = systemRange->second->begin(); s != systemRange->second->end(); ++s){
//            //Add entity to systems
//            (*s)->AddEntity(e);
//        }
//    } else {
//        //Create new component vector if it possible and add entity to compatible systems
//        for(auto system = sm->getSystems()->begin(); system != sm->getSystems()->end(); ++system){
//            //Check bits
//            if ( system->second->CompatibleWithConponents( e->componentBits ) ){
//                //Add entyty to system
//                system->second->AddEntity(e);
//                //Add system to accept list
//                sm->addSystemWithComponentBits(system->second, e->componentBits);
//            }
//        }
//    }
//    //Add entity to list
}
void World::changeEntity(Entity *e){ //Move to System Manager
//    SystemsBitset enabledSystems;
//    enabledSystems.reset();
//    ComponentsBitset  resultComponentBits = *e->componentBits & *e->disabledComponetBits;
    ComponentsBitset  resultComponentBits = *e->componentBits & *e->disabledComponetBits;

////    Take a systems
//    auto systemRange = sm->systemsByComponentHash.find(resultComponentBits);
//    //If result is not empty
//    if ( systemRange != sm->systemsByComponentHash.end()){
//        //Check for compatibility
//        for (auto s = systemRange->second->begin(); s != systemRange->second->end(); ++s){
//            //If current system is not compatible with entity
//            if (!(*s)->CompatibleWithConponents(&resultComponentBits)){
//                //Remove entity from system
////                (*s)->DeleteEntity(e);
////                e->systemBits->reset((*s)->id); //Unmark system
//            }
//            else {
//                //Dont delete entity from system and set bit
////                enabledSystems.set((*s)->id);
//                e->systemBits->set((*s)->id); //Mark system
//            };
//        }
//    }
    //Try to fing existing set
    auto systemRange = sm->systemsByComponentHash.find(resultComponentBits);
    //if exists
    if ( systemRange != sm->systemsByComponentHash.end()){
//        for(auto system = sm->getSystems()->begin(); system != sm->getSystems()->end(); ++system){
        for (auto s = systemRange->second->begin(); s != systemRange->second->end(); ++s){
            //Check bits
            if ( (*s)->CompatibleWithConponents( &resultComponentBits ) ){
                //If not present in system
//                if ( !enabledSystems.test(system->second->id) ) {
                if ( !e->systemBits->test((*s)->id) ) {
                    //Add entyty to system
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
//                if ( !enabledSystems.test(system->second->id) ) {
                    //Add entyty to system
                    system->second->AddEntity(e);
                }
                //Add system to accept list
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