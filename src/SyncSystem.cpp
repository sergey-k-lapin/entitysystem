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
    for (auto it = outEntitySet->begin(); it != outEntitySet->end();){
        Entity* e = *it;
#ifdef ENTITY_CHANGE_AUTOLOCK
        e->lock();
#endif
        if (this->CompatibleWithConponents(e->componentBits)){
            this->processEntity(e);
            ++it;
        } else {
            e->systemBits->reset(this->id);
            it = outEntitySet->erase(it);
        }
#ifdef ENTITY_CHANGE_AUTOLOCK
        e->unlock();
#endif
    }
}
