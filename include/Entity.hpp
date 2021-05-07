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
    virtual void dummy() {}
    EntityID id;
};
#include <iostream>
class Cat : public Entity {
public:
    Cat(EntityID id) : Entity(id) {}
    void meow() { std::cout << "ID: " << id << std::endl; }
};
