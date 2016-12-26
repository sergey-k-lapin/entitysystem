//
//  BehaviorType.h
//  SDL2_OPENGL_DEFAULT
//
//  Created by Сергей Лапин on 25.12.16.
//  Copyright © 2016 lapingames.com. All rights reserved.
//

#ifndef BehaviorType_h
#define BehaviorType_h

#include <typeinfo>
#include <map>
#include <Behavior.h>

struct behavior_type_comparator {
    bool operator ()(const std::type_info* a, const std::type_info* b) const {
        return a->before(*b);
    }
};
class BehaviorType {
public:
    template <typename behaviorType>
    static unsigned int GetIndex(){
        return GetIndexFor(&typeid(behaviorType));
    };
    static unsigned int GetIndex(Behavior *b);
    unsigned int id;
private:
    BehaviorType();
    static unsigned int GetIndexFor(const std::type_info *id);
    static unsigned int INDEX;
    static std::map <const std::type_info*, unsigned int, behavior_type_comparator> behaviorTypes;
};

#endif /* BehaviorType_h */
