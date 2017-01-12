//
//  behavior.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 06.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include <Behavior.h>

Behavior::~Behavior(){
    
}

//int Behavior::getCompatibleState(Entity* e){
//    return 0;
//}

void Behavior::addState(State* state){
    states[state->name] = state;
};

int Behavior::linkStatesByName(char* from, char* to){
    return this->linkStatesByName(from, to, new Transition());
}

int Behavior::linkStatesByName(char* from, char* to, Transition* transition){
    State* stateFrom = states[from];
    State* stateTo = states[to];
    if (stateFrom && stateTo){
        stateFrom->linkTo(stateTo, transition);
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

State* Behavior::getDefaultState(){
    if (this->defaultState == NULL){
        auto d = states.begin();
        if (d!= states.end()){
            this->defaultState = d->second;
        }
    }
    return this->defaultState;
}


State* Behavior::getState(char* name){
    return states[name];
}

