/* 
 * File:   SystemManager.cpp
 * Author: sergey-k-lapin
 * 
 * Created on 1 мая 2015 г., 10:32
 */

#include "SystemManager.h"
#include "World.h"

SystemManager::SystemManager(World *w) {
    this->world = w;
}

SystemManager::~SystemManager() {
}

void SystemManager::registerSystem(System *sys) {
    //Cache bitset
    std::bitset<128> componentBits = sys->getComponetBits();
    // Find compatible systems
    for (auto systemIterator = systemsByComponentHash.begin(); systemIterator != systemsByComponentHash.end(); ++systemIterator){
        if (systemIterator->first.count() > componentBits.count()){
            //Found component vector is bigger, check bits
            if ((systemIterator->first & componentBits) == componentBits){
                //Found componetVector includes current
                systemIterator->second->push_back(sys);
            }
        }
    }
    //Add system
    addSystemWithComponentBits(sys, &componentBits);
    //Mask full acception vector
    componentsAcceptedByAllSystems |= sys->getComponetBits();
    //Add system to system list.
    systems.insert(std::pair<int, System*>(sys->id, sys));
}

void SystemManager::addSystemWithComponentBits(System* sys, std::bitset<128>* componentBits){
    auto systemsForComponents = systemsByComponentHash.find(*componentBits);
    if (systemsForComponents != systemsByComponentHash.end()){
        systemsForComponents->second->push_back(sys);
    } else {
        std::vector<System*>* newSystems = new std::vector<System*>();
        newSystems->push_back(sys);
        systemsByComponentHash.insert(std::pair<std::bitset<128>, std::vector<System*>*>(*componentBits, newSystems));
    }

}

//std::map<int, System*>* SystemManager::getSystemsByComponentType(ComponentType* type){
//    std::map<ComponentType*, std::map<int, System*>*>::iterator sysMap = systemsByComponents.find(type);
//    return (*sysMap).second;
//}

std::bitset<128>* SystemManager::getComponentsAcceptedByAllSystems(){
    return &componentsAcceptedByAllSystems;
}

std::unordered_map<int, System*> *SystemManager::getSystems(){
    return &systems;
}