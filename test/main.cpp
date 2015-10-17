/* 
 * File:   main.cpp
 * Author: sergeylapin
 *
 * Created on 22 Сентябрь 2014 г., 22:01
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <bitset>
#include <typeinfo>
#include <stdio.h>

#include "ComponentType.h"
#include "Entity.h"
#include "System.h"
#include "SystemManager.h"
#include "SystemType.h"
#include "EntityManager.h"
#include <unistd.h>


//template <class T>
//void dumpobject(T const *t) {
//    unsigned char const *p = reinterpret_cast<unsigned char const *>(t);
//    for (size_t n = 0 ; n < sizeof(T) ; ++n)
//        printf("%02d ", p[n]);
//    printf("\n");
//}

//class descriptionComponent: public Component{
//public:
//    descriptionComponent(char *name){
//        this->name = name;
//    }
//    ~descriptionComponent(){};
//    char* name;
//};
//class movementComponent:public Component{
//public: 
//    movementComponent(float _x, float _y){ x = _x; y = _y; };
//    ~movementComponent(){};
//    float x;
//    float y;
//};
//
//class collisionSystem:public System{
//    collisionSystem(){
//        AcceptComponentType<movementComponent>();
//    };
////    ~collisionSystem(){};
//    void processEntity(Entity *e){
//
//    }
//};
//
//class movementSystem:public System{
//public:
//    movementSystem(){
//        AcceptComponentType<movementComponent>();
////        AcceptComponentType<descriptionComponent>();
//    }
////    ~movementSystem(){};
//    void processEntity(Entity *e){
//
//    }
//};
//
//class statSystem: public System {
//public:
//    statSystem(){
//        AcceptComponentType<descriptionComponent>();
//        AcceptComponentType<movementComponent>();
//    };
//    void processEntity(Entity *e){
//        descriptionComponent* dc = (descriptionComponent*)e->getComponent<descriptionComponent>();
//        movementComponent* mc = (movementComponent*)e->getComponent<movementComponent>();
//        std::cout << "Entyty name: " << dc->name << std::endl;
//        printf("Position (%f,%f)\n",mc->x, mc->y);
//    }
//};
//
class C1: public Component{
public:
    C1(int a){ this->a = a;}
    ~C1(){ }
    int a;
};

class C2: public Component{
public:
    C2(int a){ this->a = a;};
    ~C2(){};
    int a;
};


class S1:public System{
public:
    S1(World* w) :System(w){
        AcceptComponentType<C1>();
    }
    void processEntity(Entity *e){

    }
};

class S2:public System{
public:
    S2(World* w) :System(w){
        AcceptComponentType<C2>();
    }
    void processEntity(Entity *e){

    }
};

class S3:public System{
public:
    S3(World* w) :System(w){
        AcceptComponentType<C1>();
        AcceptComponentType<C2>();
    }
    void processEntity(Entity *e){

    }
};
using namespace std;

//class tt:public Thread {
//    void InternalThreadEntry(){
//        std::cout<<"Thread."<<std::endl;
//    }
//};

int main(int argc, char** argv) {
    World* world = new World();
    
    S1* s1 = new S1(world);
    S2* s2 = new S2(world);
    S3* s3 = new S3(world);
    
    world->getSystemManager()->registerSystem(s3);
    world->getSystemManager()->registerSystem(s1);
    world->getSystemManager()->registerSystem(s2);
        
    Entity* e1 = new Entity(world);
    world->addEntity( e1 );
    
    e1->addComponent(new C2(1));
 //   world->getEntityManager()->applyChanges();
//    s1->process();
//    s2->process();
//    s3->process();
    std::cout << " -------------------------" << std::endl;
    sleep(10);

    e1->addComponent(new C1(0));
//    world->getEntityManager()->applyChanges();
//    s1->process();
//    s2->process();
//    s3->process();
    std::cout << " -------------------------" << std::endl;
    sleep(10);
    
    e1->removeComponent<C2>();
//    world->getEntityManager()->applyChanges();
    sleep(10);
//    s1->process();
//    s2->process();
//    s3->process();
    std::cout << " -------------------------" << std::endl;
    
//    ComponentManager *cm = new ComponentManager(world);
//    SystemManager *sm = new SystemManager(world);

//    movementSystem *ms = new movementSystem();
//    statSystem *ssm = new statSystem();
//    std::cout << "Accept components: \n" << ssm->acceptList.size() << std::endl;
//    world->getSystemManager()->registerSystem(ssm);
//    world->getSystemManager()->registerSystem(ms);
//    
//    Entity *player = new Entity(world);
//    player->addComponent( new movementComponent(0.1, 0.2));
//    player->addComponent( new descriptionComponent("NEW PLAYER") );
//    player->addToWorld();
    
//    movementComponent* mc = (movementComponent*)player->getComponent<movementComponent>();
//    descriptionComponent* dc = (descriptionComponent*)player->getComponent<descriptionComponent>();
//    printf("player.x: %f\nplayer.y: %f\n",mc->x, mc->y);
//    printf("player.name: %s\n",dc->name);

//    ms->process();
//    ssm->process();
//    tt* t = new tt();
//    t->StartInternalThread();
//    t->WaitForInternalThreadToExit();
    
    return 0;
}

