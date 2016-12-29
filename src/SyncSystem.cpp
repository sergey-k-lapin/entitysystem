/* 
 * File:   SyncSystem.cpp
 * Author: sergey
 * 
 * Created on November 9, 2015, 9:18 PM
 */

#include <SyncSystem.h>

SyncSystem::SyncSystem(World *w): System(w) {
}

SyncSystem::~SyncSystem() {
}

void SyncSystem::process(){
//    ApplyRemove();
    for (auto it = outEntitySet->begin(); it != outEntitySet->end();){
        Entity* e = *it;
        e->lock();
        if (this->CompatibleWithConponents(e->componentBits)){
            this->processEntity(e);
            ++it;
        } else {
//            std::cout << "Remove entity " << e << " from " << this << std::endl;
            e->systemBits->reset(this->id);
            it = outEntitySet->erase(it);
        }
        e->unlock();
    }
//    ApplyAdd();
}
