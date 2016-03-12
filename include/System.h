/* 
 * File:   System.h
 * Author: sergey-k-lapin
 *
 * Created on 27 апреля 2015 г., 22:48
 */

#ifndef SYSTEM_H
#define	SYSTEM_H
#include "Entity.h"
#include "ComponentType.h"
//#include <map>
//#include <vector>
#include <bitset>
#include <unordered_set>
#include <deque>
//#include "Thread.h"

class World;

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
    bool CompatibleWithConponents(std::bitset<128>* componentVector);
    std::bitset<128> getComponetBits();
    std::unordered_set<Entity*> entitySet;
    void ApplyChanges();
    void ApplyRemove();
    void ApplyAdd();
    
    unsigned int id;
//    bool autoUpdate = false; 
    int Lock(pthread_mutex_t* mutex);
    int Unlock(pthread_mutex_t* mutex);
    
protected:
//    void InternalThreadEntry();
//    pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
//    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    static unsigned int _ID;
    std::bitset<128> componentBits;
    World* world;
    std::deque<Entity*> added;
    std::deque<Entity*> removed;
    };

#endif	/* SYSTEM_H */

