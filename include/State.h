//
//  command.hpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef state_h
#define state_h

#include <stdio.h>
#include <map>
#include <Goal.h>
#include <entitysystem.h>

struct command_map_comparator {
    bool operator()(Goal* a, Goal* b) const {
        return a->priority < b->priority;
    }
};

class State {
public:
    State(char* name);
    virtual void enter(Entity* e);
    virtual void exit(Entity* e);
    virtual void cancel(Entity* e);
    void linkTo(State* state);
    void linkTo(State* state, Goal* goal);
    template <typename CType>
    void AcceptComponentType(){
        AcceptComponentType(ComponentType::getTypeFor<CType>());
    };
    void AcceptComponentType( ComponentType *type );

    State* check(Entity* e);
//    std::unordered_map<Goal*,Command*> links;
    std::map<Goal*, State*, command_map_comparator> links;
    char* name;

protected:
    ComponentsBitset requiredComponents;
};

#endif /* state_h */
