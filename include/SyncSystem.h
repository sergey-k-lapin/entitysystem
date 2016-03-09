/* 
 * File:   SyncSystem.h
 * Author: sergey
 *
 * Created on November 9, 2015, 9:18 PM
 */

#ifndef SYNCSYSTEM_H
#define	SYNCSYSTEM_H
#include <System.h>


class SyncSystem:public System {
public:
    SyncSystem(World *w);
    virtual ~SyncSystem();
    void process();
private:

};

#endif	/* SYNCSYSTEM_H */

