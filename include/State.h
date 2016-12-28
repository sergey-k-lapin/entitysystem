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
#include <unordered_set>
#include <Transition.h>
#include <entitysystem.h>

struct command_map_comparator {
    bool operator()(Transition* a, Transition* b) const {
        return a->priority < b->priority;
    }
};

class State {
public:
    State(char* name);
    virtual ~State(){};
    
    void linkTo(State* state);
    void linkTo(State* state, Transition* goal);
    template <typename CType>
    void AcceptComponentType(){
        AcceptComponentType(ComponentType::getTypeFor<CType>());
    };
    void AcceptComponentType( ComponentType *type );
    bool Compatible(Entity* e);
    State* change(Entity* e);
//    std::unordered_map<Goal*,Command*> links;
    std::map<Transition*, State*, command_map_comparator> links;
    std::unordered_map<State*, Transition*> child;
    char* name;

protected:
    ComponentsBitset requiredComponents;
};

#endif /* state_h */
