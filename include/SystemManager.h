/* 
 * File:   SystemManager.h
 * Author: sergey-k-lapin
 *
 * Created on 1 мая 2015 г., 10:32
 */

#ifndef SYSTEMMANAGER_H
#define	SYSTEMMANAGER_H
#include "Entity.h"
#include "ComponentType.h"
#include "SystemType.h"
#include "System.h"
#include <map>
#include <bitset>
#include <unordered_map>
#include <unordered_set>

class World;

class SystemManager {
public:
    SystemManager( World *w);
//    SystemManager(const SystemManager& orig);
    virtual ~SystemManager();
    void registerSystem(System *sys);
//    int addEntityWithNewComponentVector(Entity *e); //TODO: Remove to comtonent manager
    void addSystemWithComponentBits(System* sys, ComponentsBitset* componentBits);
    std::map<int, System*>* getSystemsByComponentType(ComponentType* type);
    ComponentsBitset* getComponentsAcceptedByAllSystems();
    std::unordered_map<ComponentsBitset, std::vector<System*>*> systemsByComponentHash;
    std::unordered_map<int, System*> *getSystems();
    
    std::unordered_map<ComponentType*, SystemsBitset*> SystemsForComponent; //TODO: Move to System manager
    void addSystemToComponetMap(System *sys, ComponentType *type);
    std::unordered_map<int, System*> systems;

private:
//    std::map<ComponentType*, std::map<int, System*>*> systemsByComponents;
//    std::unordered_multimap<std::bitset<128>, System*> systemsByComponentHash;
    World *world;
    ComponentsBitset componentsAcceptedByAllSystems;
    
};

#endif	/* SYSTEMMANAGER_H */

