#pragma once
#include "Utils/Utils.hpp"

class Component {
public:
    Component(EntityID ownerID) : id(ownerID) {}
    EntityID ownerID() { return id; }
private:
    virtual void dummy() {}
    EntityID id;
};
