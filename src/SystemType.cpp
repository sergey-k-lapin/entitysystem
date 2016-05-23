/* 
 * File:   SystemType.cpp
 * Author: sergey-k-lapin
 * 
 * Created on 1 мая 2015 г., 14:28
 */

#include "SystemType.h"

int SystemType::ID = 1;
std::map<const std::type_info*, int, type_info_comparator2> SystemType::systemTypes;

SystemType::SystemType() {
}

SystemType::SystemType(const SystemType& orig) {
}

SystemType::~SystemType() {
}

int SystemType::getType(System* sys){
    return GetTypeId(&typeid(*sys));
}

int SystemType::GetTypeId(const std::type_info *id){
    int type = systemTypes[id];
    if (type == 0x0) {
        type = ID++;
        systemTypes[id] = type;
    }
    return type;
}