/* 
 * File:   System.h
 * Author: sergey-k-lapin
 *
 * Created on 27 апреля 2015 г., 22:48
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include <bitset>
#include <unordered_set>
#include <deque>

#include <Entity.h>
#include <ComponentType.h>
#include <SystemManager.h>

class World;
class SystemType;
class SystemManager;
class EntityManager;


class System {
public:
    System(World* w);
    virtual ~System();
    virtual void processEntity(Entity *e){};
    template <typename CType>
    void AcceptComponentType(){
        AcceptComponentType(ComponentType::getTypeFor<CType>());
    };
    void AcceptComponentType(ComponentType* type);
    virtual void AddEntity(Entity* e);
    virtual void DeleteEntity(Entity* e);
    bool CompatibleWithConponents(ComponentsBitset* componentVector);
    ComponentsBitset getComponetBits();
    std::unordered_set<Entity*>* outEntitySet;
    std::unordered_set<Entity*>* inEntitySet;
    unsigned int id;
    int Lock(pthread_mutex_t* mutex);
    int Unlock(pthread_mutex_t* mutex);
    void UpdateInContext();
    void UpdateOutContext();
    
protected:
    static unsigned int _ID;
    ComponentsBitset componentBits;
    World* world;    
};

#endif	/* SYSTEM_H */

