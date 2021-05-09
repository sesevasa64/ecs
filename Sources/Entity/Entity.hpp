#pragma once
#include "Component/Manager.hpp"
#include "Utils/Utils.hpp"

class Entity {
public:
    Entity(EntityID id, ComponentManager& manager);
    EntityID ID() { return id; }
protected:
    template<typename T, typename... ARGS>
    RefDevidedComponent<T> createComponent(ARGS&&... args) {
        return manager.createComponent<T>(id, std::forward<ARGS>(args)...);
    }
private:
    ComponentManager& manager;
    EntityID id;
};
