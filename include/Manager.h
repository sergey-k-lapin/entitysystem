/* 
 * File:   Manager.h
 * Author: sergeylapin
 *
 * Created on 28 Сентябрь 2014 г., 14:13
 */

#ifndef MANAGER_H
#define	MANAGER_H

class Entity;
class World;

class Manager {;
public:
    Manager();
    virtual ~Manager();
    
    virtual void added(Entity *e){};
    virtual void changed(Entity *e){};
    virtual void deleted(Entity *e){};
    virtual void enabled(Entity *e){};
    virtual void disabled(Entity *e){};

private:
    
protected:
    World *world;
    virtual void initialize(){};
    void setWorld(World *world);
    World *getWorld();
};

#endif	/* MANAGER_H */

