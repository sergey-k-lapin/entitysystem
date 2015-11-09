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
    for (auto it = entitySet.begin(); it != entitySet.end(); ++it){
        this->processEntity(*it);
    }
    this->ApplyChanges();
}
