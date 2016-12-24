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
        State* result = e->currentCommand->check(e);
        if (result) {
            e->currentCommand->exit(e);
            e->currentCommand = result;
            e->currentCommand->enter(e);
            return 0;
        }
    }
    return -1;
}

int Behavior::cancelCommand(BEntity* e) {
    e->currentCommand->cancel(e);
    return 0;
}

int Behavior::getCompatibleState(Entity* e){
    return 0;
}

void Behavior::addState(State* state){
    states[state->name] = state;
};

int Behavior::linkStatesByName(char* from, char* to){
    return this->linkStatesByName(from, to, new Goal());
}

int Behavior::linkStatesByName(char* from, char* to, Goal* goal){
    State* stateFrom = states[from];
    State* stateTo = states[to];
    if (stateFrom && stateTo){
        stateFrom->linkTo(stateTo, goal);
        return 0;
    }
    else return -1;
}

int Behavior::setDefault(char* name){
    if (this->states[name]){
        this->defaultState = states[name];
        return 0;
    }
    return -1;
}

int Behavior::enterState(BEntity* e, char* name){
    if (e->currentCommand) {
        e->currentCommand->exit(e);
        State* s = this->states[name];
        if (s) {
            s->enter(e);
            return 0;
        }
        return -1;
    }
    return -1;
}


State* Behavior::getDefaultState(){
    if (this->defaultState == NULL){
        auto d = states.begin();
        if (d!= states.end()){
            this->defaultState = d->second;
        }
    }
    return this->defaultState;
}



