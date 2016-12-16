/* 
 * File:   ComponentType.cpp
 * Author: sergeylapin
 * 
 * Created on 27 Сентябрь 2014 г., 12:14
 */

#include <ComponentType.h>

int ComponentType::INDEX = 0;
std::map <const std::type_info*, ComponentType*, type_info_comparator> ComponentType::componentTypes;

ComponentType::ComponentType() {
        index = INDEX++;
}

ComponentType::ComponentType(Component *type) {
        index = INDEX++;
        this->type = type;
}

ComponentType::~ComponentType() {
}

int ComponentType::getIndex(){
    return index;
}

ComponentType* ComponentType::getTypeFor(Component *c){
    return getType(&typeid(*c));
}

ComponentType* ComponentType::getType(const std::type_info* id){
    ComponentType *type = componentTypes[id];
        if (type == 0x0){
        type = new ComponentType();
        componentTypes[id] = type;
    }
    return type;    
}

int ComponentType::getIndexFor(Component *c){
    return getTypeFor(c)->getIndex();
}