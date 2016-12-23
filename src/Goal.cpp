//
//  goal.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include "goal.h"
Goal::Goal(){
    priority = 0;
};

Goal::Goal(int priority){
    this->priority = priority;
};

bool Goal::check(Entity* e) {
    return true;
};

