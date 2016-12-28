//
//  Transition.h
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 26.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef Transition_h
#define Transition_h
#include <stdio.h>
#include <Entity.h>

class Transition {
public:
    Transition();
    Transition(int priority);
    virtual bool make(Entity* e);
    int priority;
};

#endif /* Transition_h */
