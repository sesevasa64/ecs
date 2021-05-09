#pragma once
#include "Component/Manager.hpp"
#include "Utils/Utils.hpp"

class EntityManager;

class Entity {
public:
    EntityID ID() { return id; }
    virtual void Start() {}
    friend class EntityManager;
protected:
    template<typename T, typename... ARGS>
    RefDevidedComponent<T> createComponent(ARGS&&... args) {
        return manager->createComponent<T>(id, std::forward<ARGS>(args)...);
    }
private:
    void setComponentManager(ComponentManager* manager) { this->manager = manager; }
    void setID(EntityID id) { this->id = id; }
    ComponentManager* manager;
    EntityID id;
};
