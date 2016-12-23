//
//  command.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include "command.h"

Command::Command(char* name){
    this->name = name;
};

void Command::enter(Entity* e){
    
};

void Command::exit(Entity* e){
    
};

void Command::cancel(Entity* e){
    
}

void Command::linkTo(Command* state){
    this->linkTo(state, new Goal());
};

void Command::linkTo(Command* state, Goal* goal){
    this->links[goal] = state;
};

Command* Command::check(Entity* e){
    for (auto link = links.begin(); link != links.end(); ++link){
        if (link->first->check(e)){
            return (link->second);
        }
    }
    return NULL;
};

void Command::AcceptComponentType(ComponentType *type){
    this->requiredComponents.set(type->getIndex());
}

