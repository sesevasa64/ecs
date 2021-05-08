#pragma once
#include <unordered_map>
#include "Component/Component.hpp"

using ComponentIt = Map<EntityID, RefComponent>::iterator;
using ComponentMap = Map<TypeID, Map<EntityID, RefComponent>>;

class ComponentManager {
public:
    template<typename T>
    class Iterator {
    public:
        Iterator(ComponentIt it) : it(it) {}
        Iterator& operator++() {
            it++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator iter(it);
            it++;
            return iter;
        }
        RefDevidedEntity<T> operator->() {
            return std::static_pointer_cast<T>(it->second);
        }
        RefDevidedEntity<T> operator*() {
            return std::static_pointer_cast<T>(it->second);
        }
        bool operator==(const Iterator& other) {
            return it == other.it;
        }
        bool operator!=(const Iterator& other) {
            return it != other.it;
        }
    private:
        ComponentIt it;
    };
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
        return std::static_pointer_cast<T>(map[typeID][id]);
    }
    template<typename T>
    Iterator<T> begin() {
        TypeID typeID = TypeInfo::get<T>();
        return Iterator<T>(map[typeID].begin());
    }
    template<typename T>
    Iterator<T>& end() {
        TypeID typeID = TypeInfo::get<T>();
        static Iterator<T> iter(map[typeID].end());
        return iter;
    }
private:
    ComponentMap map;
};
