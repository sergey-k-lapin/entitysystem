//
//  command.hpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef command_hpp
#define command_hpp

#include <stdio.h>
#include <map>
#include <Goal.h>
#include <entitysystem.h>

struct command_map_comparator {
    bool operator()(Goal* a, Goal* b) const {
        return a->priority < b->priority;
    }
};

class Command {
public:
    Command(char* name);
    virtual void enter(Entity* e);
    virtual void exit(Entity* e);
    virtual void cancel(Entity* e);
    void linkTo(Command* state);
    void linkTo(Command* state, Goal* goal);
    template <typename CType>
    void AcceptComponentType(){
        AcceptComponentType(ComponentType::getTypeFor<CType>());
    };
    void AcceptComponentType( ComponentType *type );

    Command* check(Entity* e);
//    std::unordered_map<Goal*,Command*> links;
    std::map<Goal*, Command*, command_map_comparator> links;
    char* name;

protected:
    ComponentsBitset requiredComponents;
};

#endif /* command_hpp */
