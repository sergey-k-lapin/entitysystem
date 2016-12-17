//
//  bentity.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include "bentity.h"
#include "Behavior.h"
#include "command.h"

BEntity::BEntity(World* w):Entity(w){
    
}
int BEntity::nextCommand(){
    if (this->behavior){
        return this->behavior->next(this);
    }
    return NULL;
}
void BEntity::assignBehavior(Behavior* b){
    this->behavior = b;
    this->currentCommand = b->getDefaultCommand();
}

int BEntity::cancelCommand(){
    if (this->behavior){
        return this->behavior->cancelCommand(this);
    }
    return NULL;
};
