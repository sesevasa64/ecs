#pragma once
#include <memory>
#include "Utils.hpp"

class IEntity {
public:
    IEntity(EntityID id) : id(id) {}
    EntityID ID() { return id; }
private:
    virtual void dummy() {}
    EntityID id;
};

using RefEntity = std::shared_ptr<IEntity>;
template<typename T>
using RefDevidedEntity = std::shared_ptr<T>;
