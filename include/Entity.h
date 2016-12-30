/* 
 * File:   Entity.h
 * Author: sergeylapin
 *
 * Created on 22 Сентябрь 2014 г., 22:14
 */

#ifndef ENTITY_H
#define	ENTITY_H


#include <config.h>
#include <vector>
#include <unordered_set>
#include <ComponentType.h>
#include <World.h>
#include <assert.h>

class Component;
class ComponentType;
class World;
class ComponentManager;

//! Сущность
class Entity {
public:
    /** \brief Конструктор\n Class constructor
     \details Создаем экземпляр сущности
     */
    /*!
     \param world ссылка на мир
     */
    Entity(World *world);
    //! Деструктор\n
    //! Class destructor
    virtual ~Entity();    
    //! Получить битовую маску компонентов\n
    //! Get components bit mask
    ComponentsBitset *getComponentBits();
    //! Получить битоваую маску сисем\n
    //! Get systems bit mask
    SystemsBitset *getSystemBits();
    //! Получить ссылку на компонент
    template <typename c>
    Component *getComponent(){
        return this->getComponent(ComponentType::getTypeFor<c>());
    };
    Component *getComponent(ComponentType *type);
    void addToWorld();
    void deleteFromWorld();
    World *getWorld();
    Entity* addComponent(Component *component);
    Entity* addComponent(Component *component, ComponentType *type);
    template <typename c>
    Entity* removeComponent(){
        return this->removeComponent(ComponentType::getTypeFor<c>());
    };
    Entity* removeComponent(Component *component);
    Entity* removeComponent(ComponentType* type);
    Entity* removeComponent(Component* component, ComponentType* type);
    void update();
    int lock();
    int unlock();
    void addToChange();
    //! Битовая маска компонентов\n
    //! Components bit mask
    ComponentsBitset *componentBits;
    //! Битовая маска систем\n
    //! Systems bit mask
    SystemsBitset *systemBits;
    //! Ссылка на объект World\n
    //! Pointer to World
    World *world;
    //! Идентификатор сущности\n
    //! Entity's ID
    int id;
private:
    static int INDEX;
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexAttr;
    std::unordered_map<ComponentType*, Component*> components;
};

#endif	/* ENTITY_H */

