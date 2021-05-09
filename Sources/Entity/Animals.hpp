#pragma once
#include <iostream>
#include "Entity/Entity.hpp"
#include "Component/Position.hpp"

class Cat : public Entity {
public:
    Cat(EntityID id, ComponentManager& manager) : Entity(id, manager) {
        position = createComponent<Position>(1, 2, 3);
    }
    ~Cat() { std::cout << "Cat: " << ID() << ", destructor" << std::endl; }
    void meow() { std::cout << "ID: " << ID() << std::endl; }
private:
    RefDevidedComponent<Position> position;
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
