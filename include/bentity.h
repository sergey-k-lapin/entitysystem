//
//  bentity.hpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef bentity_hpp
#define bentity_hpp

#include <stdio.h>
#include <entitysystem.h>

class Behavior;
class Command;

class BEntity: public Entity {
public:
    BEntity(World* w);
    int nextCommand();
    int cancelCommand();
    void assignBehavior(Behavior* b);
//protected:
    Command* currentCommand = NULL;
    Behavior* behavior = NULL;
};

#endif /* bentity_hpp */
