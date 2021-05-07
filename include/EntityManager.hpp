#pragma once
#include <memory>
#include <unordered_map>
#include "Entity.hpp"
#include "Utils.hpp"

template<typename T, typename U>
using Map = std::unordered_map<T, U>;

class EntityManager {
public:
    template<typename T, typename... ARGS>
    RefDevidedEntity<T> createEntity(ARGS&&... args) {
        TypeID typeID = TypeInfo::get<T>();
        RefDevidedEntity<T> entity = std::make_shared<T>(id, std::forward<ARGS>(args)...);
        map[typeID][id++] = entity;
        return entity;
    }
    template<typename T>
    RefDevidedEntity<T> getEntity(EntityID id) {
        TypeID typeID = TypeInfo::get<T>();
        return std::dynamic_pointer_cast<T>(map[typeID][id]);
    }
private:
    Map<TypeID, Map<EntityID, RefEntity>> map;
    EntityID id = 0;
};
