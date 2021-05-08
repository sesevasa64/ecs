#pragma once
#include <memory>
#include "Utils/Utils.hpp"

class Entity;
using RefEntity = std::shared_ptr<Entity>;
template<typename T>
using RefDevidedEntity = std::shared_ptr<T>;
using RefWeakEntity = std::weak_ptr<Entity>;
template<typename T>
using RefDevidedWeakEntity = std::weak_ptr<T>;
#include <iostream>
class Entity {
public:
    Entity(EntityID id) : id(id) {}
    EntityID ID() { return id; }
    virtual ~Entity() {}
protected:
    template<typename T>
    void createComponent();
private:
    virtual void dummy() {}
    EntityID id;
};

class Cat : public Entity {
public:
    Cat(EntityID id) : Entity(id) {}
    ~Cat() { std::cout << "Cat: " << ID() << ", destructor" << std::endl; }
    void meow();
};

class Dog : public Entity {
public:
    Dog(EntityID id) : Entity(id) {}
    ~Dog() { std::cout << "Dog: " << ID() << ", destructor" << std::endl; }
};

class Floppa : public Entity {
public:
    Floppa(EntityID id) : Entity(id) {}
    ~Floppa() { std::cout << "Floppa: " << ID() << ", destructor" << std::endl; } 
};
