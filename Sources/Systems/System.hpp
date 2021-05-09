#pragma once
#include "Component/Manager.hpp"

class System {
public:
    System(ComponentManager& manager) : manager(manager) {}
    virtual void PreUpdate() {}
    virtual void Update() {}
    virtual void PostUpdate() {}
protected:
    ComponentManager& manager;
};
