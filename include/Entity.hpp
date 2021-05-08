#pragma once
#include <memory>
#include "Utils.hpp"

class Entity;
using RefEntity = std::shared_ptr<Entity>;
template<typename T>
using RefDevidedEntity = std::shared_ptr<T>;

class Entity {
public:
    Entity(EntityID id) : id(id) {}
    EntityID ID() { return id; }
protected:
    template<typename T>
    void createComponent();
private:
    virtual void dummy() {}
    EntityID id;
};
#include <iostream>
class Cat : public Entity {
public:
    Cat(EntityID id) : Entity(id) {}
    void meow() { std::cout << "ID: " << ID() << std::endl; }
};
class Dog : public Entity {
public:
    Dog(EntityID id) : Entity(id) {}
};
class Floppa : public Entity {
public:
    Floppa(EntityID id) : Entity(id) {} 
};
