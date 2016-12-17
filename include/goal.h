//
//  goal.hpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef goal_hpp
#define goal_hpp
#include <entitysystem.h>

#include <stdio.h>
class Goal {
public:
    virtual bool check(Entity* e);
};

//class Pass: public Goal {
//public:
//    bool check(Entity* e) {
//        return true;
//    }
//};

#endif /* goal_hpp */
