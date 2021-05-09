#pragma once
#include <unordered_map>
#include "Component/Component.hpp"

using ComponentIt = Map<EntityID, RefWeakComponent>::iterator;
using ComponentMap = Map<TypeID, Map<EntityID, RefWeakComponent>>;
using ComponentMapIt = ComponentMap::iterator;

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
            return std::static_pointer_cast<T>(it->second.lock());
        }
        RefDevidedEntity<T> operator*() {
            return std::static_pointer_cast<T>(it->second.lock());
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
    template<typename T>
    struct Deleter {
        Deleter(ComponentMap& map) : map(map) {}
        void operator()(T *p) {
            static TypeID typeID = TypeInfo::get<T>();
            map[typeID].erase(p->ownerID());
            delete p;
        }
    private:
        ComponentMap& map;
    };
    template<typename T, typename... ARGS>
    RefDevidedComponent<T> createComponent(EntityID id, ARGS&&... args) {
        static TypeID typeID = TypeInfo::get<T>();
        static Deleter<T> deleter(map);
        Ref<T> component(new T(std::forward<ARGS>(args)...), deleter);
        component->setOwnerID(id);
        map[typeID][id] = component;
        return component;
    }
    template<typename T>
    RefDevidedComponent<T> getComponent(EntityID id) {
        static TypeID typeID = TypeInfo::get<T>();
        return std::static_pointer_cast<T>(map[typeID][id].lock());
    }
    template<typename T = Component>
    Iterator<T> begin() {
        static TypeID typeID = TypeInfo::get<T>();
        return Iterator<T>(map[typeID].begin());
    }
    template<typename T = Component>
    Iterator<T>& end() {
        static TypeID typeID = TypeInfo::get<T>();
        static Iterator<T> iter(map[typeID].end());
        return iter;
    }
private:
    ComponentMap map;
};

template<>
class ComponentManager::Iterator<Component> {
public:
    Iterator(ComponentMapIt start, ComponentMapIt end) : baseIt(start), endIt(end) {
        if (baseIt != endIt) {
            it = baseIt->second.begin();
            while (it == baseIt->second.end()) {
                if (++baseIt == endIt)
                    return;
                it = baseIt->second.begin();
            }
        }
    }
    Iterator& operator++() {
        while (++it == baseIt->second.end()) {
            if (++baseIt == endIt)
                return *this;
            it = baseIt->second.begin();
        }
        return *this;
    }
    Iterator operator++(int) {
        Iterator iter(baseIt, endIt);
        ++(*this);
        return iter;
    }
    RefComponent operator->() {
        return it->second.lock();
    }
    RefComponent operator*() {
        return it->second.lock();
    }
    bool operator==(const Iterator& other) {
        return baseIt == other.baseIt;
    }
    bool operator!=(const Iterator& other) {
        return baseIt != other.baseIt;
    }
private:
    ComponentMapIt baseIt, endIt;
    ComponentIt it;
};

template<>
inline ComponentManager::Iterator<Component> ComponentManager::begin() {
    return Iterator<Component>(map.begin(), map.end());
}
template<>
inline ComponentManager::Iterator<Component>& ComponentManager::end() {
    static Iterator<Component> iter(map.end(), map.end());
    return iter;
}
