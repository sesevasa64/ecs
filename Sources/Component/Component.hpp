#pragma once
#include "Utils/Utils.hpp"

class ComponentManager;

class Component {
public:
    EntityID ownerID() { return id; }
    friend class ComponentManager;
private:
    void setOwnerID(EntityID ownerID) { id = ownerID; }
    EntityID id;
};
