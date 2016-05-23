/* 
 * File:   Context.h
 * Author: sergeylapin
 *
 * Created on 21 Май 2016 г., 13:49
 */

#ifndef CONTEXT_H
#define	CONTEXT_H
#include <unordered_map>
#include <unordered_set>
//#include <System.h>
//#include <Entity.h>
//
class System;
class Entity;
class Context{
public:
    Context();
    std::unordered_map< System*, std::unordered_set<Entity*>* > values;
    int id;
private:
    static int _id;
};


#endif	/* CONTEXT_H */

