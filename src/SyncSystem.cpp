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
    ApplyRemove();
    for (auto it = outEntitySet->begin(); it != outEntitySet->end(); ++it){
        this->processEntity(*it);
    }
    ApplyAdd();
}
