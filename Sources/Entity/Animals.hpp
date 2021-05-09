#pragma once
#include <iostream>
#include "Entity/Entity.hpp"
#include "Component/Position.hpp"

class Cat : public Entity {
public:
    void Start() override {
        position = createComponent<Position>(1, 2, 3);
    }
    ~Cat() { 
        std::cout << "Cat: " << ID() << ", destructor" << std::endl; 
    }
    void meow() { 
        std::cout << "ID: " << ID() << std::endl; 
    }
private:
    Ref<Position> position;
};

class Dog : public Entity {
public:
    ~Dog() { 
        std::cout << "Dog: " << ID() << ", destructor" << std::endl;
    }
};

class Floppa : public Entity {
public:
    ~Floppa() { 
        std::cout << "Floppa: " << ID() << ", destructor" << std::endl;
    } 
};
