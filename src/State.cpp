//
//  command.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include "State.h"

State::State(char* name){
    this->name = name;
};

void State::enter(Entity* e){
    
};

void State::exit(Entity* e){
    
};

void State::cancel(Entity* e){
    
}

void State::linkTo(State* state){
    this->linkTo(state, new Goal());
};

void State::linkTo(State* state, Goal* goal){
    this->links[goal] = state;
};

State* State::check(Entity* e){
    for (auto link = links.begin(); link != links.end(); ++link){
        if (link->first->check(e)){
            return (link->second);
        }
    }
    return NULL;
};

void State::AcceptComponentType(ComponentType *type){
    this->requiredComponents.set(type->getIndex());
}

