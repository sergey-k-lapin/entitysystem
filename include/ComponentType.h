/* 
 * File:   ComponentType.h
 * Author: sergeylapin
 *
 * Created on 27 Сентябрь 2014 г., 12:14
 */

#ifndef COMPONENTTYPE_H
#define	COMPONENTTYPE_H

#include "Component.h"
#include <typeinfo>
#include <map>
#include <iostream>

struct type_info_comparator {
  bool operator ()(const std::type_info* a, const std::type_info* b) const {
    return a->before(*b);
  }
};

class ComponentType {
public:
    ComponentType(Component *type);
    ComponentType();
    virtual ~ComponentType();
    int getIndex();
    static std::map <const std::type_info*, ComponentType*, type_info_comparator> componentTypes;
    template <typename c>
    static ComponentType* getTypeFor(){
        return getType(&typeid(c));
    }
    static ComponentType* getTypeFor(Component *c);
    static int getIndexFor(Component *c);
    static ComponentType* getType( const std::type_info *id);
    int index;
private:
    static int INDEX;
    Component *type;
};

#endif	/* COMPONENTTYPE_H */

