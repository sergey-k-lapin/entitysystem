/* 
 * File:   Component.h
 * Author: sergeylapin
 *
 * Created on 27 Сентябрь 2014 г., 12:08
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

class Component {
public:
    Component();
    virtual ~Component();
//    unsigned int useCount = 0;
private:
    unsigned int id;
};

#endif	/* COMPONENT_H */

