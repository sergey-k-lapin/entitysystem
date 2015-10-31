/* 
 * File:   System.cpp
 * Author: sergey-k-lapin
 * 
 * Created on 27 апреля 2015 г., 22:48
 */

#include "System.h"
#include "SystemType.h"
#include "EntityManager.h"
#include <unistd.h> //RMOVE

unsigned int System::_ID = 0;

System::System(World* w) {
    this->world = w;
    this->id = ++_ID;

    this->StartInternalThread();
}

System::~System() {
}

void System::process(){//Depricated in threaded system class
//    std::cout << typeid(*this).name() << std::endl;
//    std::cout << "Process " << entitySet.size() << std::endl;
    for (auto it = entitySet.begin(); it != entitySet.end(); ++it){
        this->processEntity(*it);
    }
    this->ApplyChanges();
    //Update changes;
//    if (autoUpdate) {
//        this->world->getEntityManager()->applyChanges();
//    }

}

void System::AddEntity(Entity* e){
//        entitySet.insert(e);
//        e->getSystemBits()->set(this->id);    
    added.push_back(e);
//  pthread_mutex_lock(&my_mutex);
    pthread_cond_signal(&cond);
//  pthread_mutex_unlock(&my_mutex);

}

void System::DeleteEntity(Entity* e){
//    entitySet.erase(e);
//    e->getSystemBits()->reset(this->id);
    
    removed.push_back(e);
}

void System::ApplyChanges() { 
    while (!added.empty()){ //Process and add all new
        Entity* e = added.front();
        e->getSystemBits()->set(this->id);
        this->processEntity(e);
        entitySet.insert(e);
        added.pop_front();
    }
    while (!removed.empty()){
        Entity* e = removed.front();
        entitySet.erase(e);
        e->getSystemBits()->reset(this->id);
        removed.pop_front();
    }
}

void System::InternalThreadEntry(){
    while(true){
//        std::cout << typeid(*this).name() << std::endl;
//        std::cout << "Process " << entitySet.size() << std::endl;

        for (auto it = entitySet.begin(); it != entitySet.end(); ++it){
            this->processEntity(*it);
//            sleep(1);
        }
        this->ApplyChanges();
        if ( entitySet.empty() && added.empty() && removed.empty() ){
            pthread_mutex_lock(&my_mutex);
//            std::cout << typeid(*this).name() << " is waiting." << std::endl;
            pthread_cond_wait(&cond, &my_mutex);
            pthread_mutex_unlock(&my_mutex);        
        }
    }
}

void System::AcceptComponentType(ComponentType *type){
    this->componentBits.set(type->getIndex());
}
std::bitset<128> System::getComponetBits(){
    return this->componentBits;
}

bool System::CompatibleWithConponents(std::bitset<128>* componentVector){
    return ( (this->componentBits & *componentVector) ==  this->componentBits);
}