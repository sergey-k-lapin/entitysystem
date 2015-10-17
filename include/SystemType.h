/* 
 * File:   SystemType.h
 * Author: sergey-k-lapin
 *
 * Created on 1 мая 2015 г., 14:28
 */

#ifndef SYSTEMTYPE_H
#define	SYSTEMTYPE_H
#include <map>
#include <typeinfo>
#include "System.h"

struct type_info_comparator2 {
  bool operator ()(const std::type_info* a, const std::type_info* b) const {
    return a->before(*b);
  }
};

class SystemType {
public:
    SystemType();
    SystemType(const SystemType& orig);
    virtual ~SystemType();
    template <typename c>
    static int getType(){
        return GetTypeId(&typeid(c));
    }
    static int getType(System* sys);
    static int GetTypeId(const std::type_info *id);
private:
    static int ID;
    static std::map<const std::type_info*, int, type_info_comparator2> systemTypes;
};

#endif	/* SYSTEMTYPE_H */

