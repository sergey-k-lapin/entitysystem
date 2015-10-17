/* 
 * File:   Manager.cpp
 * Author: sergeylapin
 * 
 * Created on 28 Сентябрь 2014 г., 14:13
 */

#include "Manager.h"

Manager::Manager() {
}

Manager::~Manager() {
}

void Manager::setWorld(World *world){
    this->world = world;
}
World *Manager::getWorld(){
    return this->world;
}