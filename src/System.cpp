/* 
 * File:   System.cpp
 * Author: sergey-k-lapin
 * 
 * Created on 27 апреля 2015 г., 22:48
 */

#include <System.h>

unsigned int System::_ID = 0;

System::System(World* w) {
    this->world = w;
    this->id = _ID++;
    
    //Create entity pool in active context
    std::unordered_set<Entity*>* dataset = new std::unordered_set<Entity*>();
    this->world->activeContext->values.insert(std::pair<System*, std::unordered_set<Entity*>*>( this, dataset ));

    this->inEntitySet = dataset;
    this->outEntitySet = dataset;
}

System::~System() {
}

void System::AddEntity(Entity* e){
    e->getSystemBits()->set(this->id);
    inEntitySet->insert(e);

}

void System::DeleteEntity(Entity* e){ //???
//    removed.push_back(e);
}

void System::ApplyRemove() { //Depricated
//    while (!removed.empty()){
//        Entity* e = removed.front();
//        inEntitySet->erase(e); //Remove entity from system
//        e->getSystemBits()->reset(this->id); //Reset system bit
//        e->lock();
//        for (auto it=e->removedComponents.begin(); it != e->removedComponents.end();) {
//            
//            if ((*it)->usedInSystems.test(this->id)) {
//                (*it)->usedInSystems.reset(this->id);
//                if ((*it)->usedInSystems.none()){
//                    e->removeFromCurrent((*it));
//                }
//                it = e->removedComponents.erase(it);                
//            } else {
//                ++it;
//            }
//        }
//        e->unlock();
//        removed.pop_front();
//    }
};

void System::ApplyAdd() { //Depricated
//    while (!added.empty()){ //Process and add all new
//        Entity* e = added.front();
//        e->getSystemBits()->set(this->id);
//        this->processEntity(e);
//        inEntitySet->insert(e);
//        added.pop_front();
//    }
};

void System::ApplyChanges() { //Depricated
//    ApplyRemove();
//    ApplyAdd();
}

void System::CheckComponent(Entity* e) { //Depricated
//    e->systemBits->reset(this->id); //Reset system bit
////    e->lock();
//    for (auto it=e->removedComponents.begin(); it != e->removedComponents.end();) {
//        if ((*it)->usedInSystems.test(this->id)) {
//            (*it)->usedInSystems.reset(this->id);
//            if ((*it)->usedInSystems.none()){
//                e->removeFromCurrent((*it));
//            }
//            it = e->removedComponents.erase(it);
//        } else {
//                    ++it;
//                }
//        }
////    e->unlock();
}

void System::AcceptComponentType(ComponentType *type){
    this->componentBits.set(type->getIndex());
    world->sm->addSystemToComponetMap(this, type);
}

ComponentsBitset System::getComponetBits(){
    return this->componentBits;
}

bool System::CompatibleWithConponents(ComponentsBitset* componentVector){
    return ( (this->componentBits & *componentVector) ==  this->componentBits);
}
int System::Lock(pthread_mutex_t* mutex){
    return pthread_mutex_lock( mutex );
}
int System::Unlock(pthread_mutex_t* mutex){
    return pthread_mutex_unlock( mutex );
}

void System::UpdateInContext(){
    this->inEntitySet = this->world->getActiveEntitySet(this);
}

void System::UpdateOutContext(){
    this->outEntitySet = this->world->getVisibleEntitySet(this);    
}