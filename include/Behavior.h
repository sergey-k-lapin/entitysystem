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
#include <State.h>
#include <Transition.h>

class Behavior {
public:
    virtual ~Behavior(); //!important for std::typeinfo()
//    int getCompatibleState(Entity* e);
    void addState(State* state);
    int linkStatesByName(char* from, char* to);
    int linkStatesByName(char* from, char* to, Transition* goal);
    int setDefault(char* name);
    State* getDefaultState();
    State* getState(char* name);
protected:
    State* defaultState = NULL;
    std::unordered_map<char*,State*> states;
};


#endif /* behavior_hpp */
