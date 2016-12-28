//
//  Transition.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 26.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include <Transition.h>

Transition::Transition(){
    priority = 0;
};

Transition::Transition(int priority){
    this->priority = priority;
};

bool Transition::make(Entity* e) {
    return true;
};