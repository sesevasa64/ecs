#pragma once
#include <memory>
#include "Utils/Utils.hpp"

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
