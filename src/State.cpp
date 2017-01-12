//
//  command.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include <State.h>

State::State(char* name){
    this->name = name;
};

void State::linkTo(State* state){
    this->linkTo(state, new Transition());
};

void State::linkTo(State* state, Transition* transition){
    links[transition] = state;
    child[state] = transition;
};

State* State::change(Entity* e){
    for (auto link = links.begin(); link != links.end(); ++link){
        Transition* transition = link->first;
        if (transition->make(e)){
            return (link->second);
        }
    }
    return NULL;
};

bool State::Compatible(Entity* e){
    return ( (requiredComponents & *e->componentBits) ==  requiredComponents);
    
};


void State::AcceptComponentType(ComponentType *type){
    this->requiredComponents.set(type->getIndex());
}

