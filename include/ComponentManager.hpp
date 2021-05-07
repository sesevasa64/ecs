#pragma once
#include <unordered_map>
#include "Component.hpp"

template<typename T, typename U>
using Map = std::unordered_map<T, U>;

class ComponentManager {
public:
    template<typename T, typename... ARGS>
    RefDevidedComponent<T> createComponent(EntityID id, ARGS&&... args) {
        TypeID typeID = TypeInfo::get<T>();
        RefDevidedComponent<T> entity = std::make_shared<T>(id, std::forward<ARGS>(args)...);
        map[typeID][id] = entity;
        return entity;
    }
    template<typename T>
    RefDevidedComponent<T> getComponent(EntityID id) {
        TypeID typeID = TypeInfo::get<T>();
        return std::dynamic_pointer_cast<T>(map[typeID][id]);
    }
private:
    Map<TypeID, Map<EntityID, RefComponent>> map;
};
