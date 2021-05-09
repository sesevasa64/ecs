#pragma once
#include <iostream>
#include "Component/Manager.hpp"
#include "Utils/Utils.hpp"

class Entity {
public:
    Entity(EntityID id, ComponentManager& manager);
    EntityID ID() { return id; }
protected:
    template<typename T, typename... ARGS>
    RefDevidedComponent<T> createComponent(ARGS&&... args) {
        return manager.createComponent<T>(id, std::forward<ARGS>(args)...);
    }
private:
    ComponentManager& manager;
    EntityID id;
};

class Cat : public Entity {
public:
    Cat(EntityID id, ComponentManager& manager) : Entity(id, manager) {}
    ~Cat() { std::cout << "Cat: " << ID() << ", destructor" << std::endl; }
    void meow();
};

class Dog : public Entity {
public:
    Dog(EntityID id, ComponentManager& manager) : Entity(id, manager) {}
    ~Dog() { std::cout << "Dog: " << ID() << ", destructor" << std::endl; }
};

class Floppa : public Entity {
public:
    Floppa(EntityID id, ComponentManager& manager) : Entity(id, manager) {}
    ~Floppa() { std::cout << "Floppa: " << ID() << ", destructor" << std::endl; } 
};
