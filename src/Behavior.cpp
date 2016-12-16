//
//  behavior.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include "Behavior.h"

int Behavior::next(BEntity* e){
    if (e->currentCommand != NULL){
        Command* result = e->currentCommand->check(e);
        if (result) {
            result->exec(e);
            e->currentCommand = result;
            return 0;
        }
    }
    return -1;
}

int Behavior::cancelCommand(BEntity* e) {
    e->currentCommand->cancel(e);
    return 0;
}

int Behavior::getCompatibleCommand(Entity* e){
    return 0;
}

void Behavior::addCommand(Command* command){
    commands[command->name] = command;
};

int Behavior::linkCommandsByName(char* from, char* to){
    return this->linkCommandsByName(from, to, new Goal());
}

int Behavior::linkCommandsByName(char* from, char* to, Goal* goal){
    Command* stateFrom = commands[from];
    Command* stateTo = commands[to];
    if (stateFrom && stateTo){
        stateFrom->linkTo(stateTo, goal);
        return 0;
    }
    else return -1;
}

int Behavior::setDefault(char* name){
    if (this->commands[name]){
        this->defaultCommand = commands[name];
        return 0;
    }
    return -1;
}

Command* Behavior::getDefaultCommand(){
    if (this->defaultCommand == NULL){
        auto d = commands.begin();
        if (d!= commands.end()){
            this->defaultCommand = d->second;
        }
    }
    return this->defaultCommand;
}



