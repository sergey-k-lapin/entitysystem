//
//  behavior.hpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef behavior_hpp
#define behavior_hpp

#include <stdio.h>
#include <entitysystem.h>
#include <State.h>
#include <Goal.h>
#include <bentity.h>

class Behavior {
public:
    int next(BEntity* e);
    int cancelCommand(BEntity* e);
    
    int getCompatibleCommand(Entity* e);
    void addCommand(State* command);
    int linkCommandsByName(char* from, char* to);
    int linkCommandsByName(char* from, char* to, Goal* goal);
    int setDefault(char* name);
    State* getDefaultCommand();
    
protected:
    State* defaultCommand = NULL;
    std::unordered_map<char*,State*> commands;
};


#endif /* behavior_hpp */
