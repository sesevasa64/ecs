#pragma once
#include <memory>
#include "Utils.hpp"

class Component;
using RefComponent = std::shared_ptr<Component>; 
template<typename T>
using RefDevidedComponent = std::shared_ptr<T>;

class Component {
public:
    Component(EntityID ownerID) : ownerID(ownerID) {}
    EntityID ID() { return ownerID; }
private:
    virtual void dummy() {}
    EntityID ownerID;
};
#include <iostream>
class Position : public Component {
public:
    Position(EntityID ownerID, double x, double y, double z) 
    : Component(ownerID), x(x), y(y), z(z) {}
    void test() { std::cout << x << " " << y << " " << z << std::endl; }
private:
    double x, y, z;
};
