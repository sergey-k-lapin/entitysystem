//
//  BehaviorType.cpp
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 25.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#include <BehaviorType.h>

unsigned int BehaviorType::INDEX = 0;
std::map <const std::type_info*, unsigned int, behavior_type_comparator> BehaviorType::behaviorTypes;

BehaviorType::BehaviorType(){
}

unsigned int BehaviorType::GetIndexFor(const std::type_info *id){
    auto type = behaviorTypes.find(id);
    if (type != behaviorTypes.end()){
        return type->second;
    } else {
        unsigned int newId = INDEX++;
        behaviorTypes.insert(std::pair<const std::type_info*, unsigned int>(id,newId));
        return newId;
    }
    return 0;
}

unsigned int BehaviorType::GetIndex(Behavior *b){
    return GetIndexFor(&typeid(*b));
};
