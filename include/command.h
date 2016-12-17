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
#include <unordered_map>
#include "goal.h"
#include <entitysystem.h>


class Command {
public:
    Command(char* name);
    virtual void exec(Entity* e);
    virtual void cancel(Entity* e);
    void linkTo(Command* state);
    void linkTo(Command* state, Goal* goal);
    template <typename CType>
    void AcceptComponentType(){
        AcceptComponentType(ComponentType::getTypeFor<CType>());
    };
    void AcceptComponentType( ComponentType *type );

    Command* check(Entity* e);
    std::unordered_map<Goal*,Command*> links;
    char* name;

protected:
    std::bitset<128> requiredComponents;
};

#endif /* command_hpp */
