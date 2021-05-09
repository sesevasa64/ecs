#pragma once
#include "Entity/Entity.hpp"
#include "Utils/Utils.hpp"

using EntityMap = Map<TypeID, Map<EntityID, RefWeakEntity>>;
using EntityIt = Map<EntityID, RefWeakEntity>::iterator;
using EntityMapIt = EntityMap::iterator;

class EntityManager {
public:
    EntityManager(ComponentManager& manager) : manager(manager) {}
    template<typename T>
    class Iterator {
    public:
        Iterator(EntityIt it) : it(it) {}
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
        EntityIt it;
    };
    template<typename T>
    struct Deleter {
        Deleter(EntityMap& map) : map(map) {}
        void operator()(T *p) {
            TypeID typeID = TypeInfo::get<T>();
            map[typeID].erase(p->ID());
            delete p;
        }
    private:
        EntityMap& map;
    };
    template<typename T, typename... ARGS>
    RefDevidedEntity<T> createEntity(ARGS&&... args) {
        static TypeID typeID = TypeInfo::get<T>();
        static Deleter<T> deleter(map);
        auto entity = std::shared_ptr<T>(new T(id, manager, std::forward<ARGS>(args)...), deleter);
        map[typeID][id++] = entity;
        return entity;
    }
    template<typename T>
    RefDevidedEntity<T> getEntity(EntityID id) {
        static TypeID typeID = TypeInfo::get<T>();
        return std::static_pointer_cast<T>(map[typeID][id].lock());
    }
    template<typename T = Entity>
    Iterator<T> begin() {
        static TypeID typeID = TypeInfo::get<T>();
        return Iterator<T>(map[typeID].begin());
    }
    template<typename T = Entity>
    Iterator<T>& end() {
        static TypeID typeID = TypeInfo::get<T>();
        static Iterator<T> iter(map[typeID].end());
        return iter;
    }
private:
    ComponentManager& manager;
    EntityMap map;
    EntityID id = 0;
};

template<>
class EntityManager::Iterator<Entity> {
public:
    Iterator(EntityMapIt start, EntityMapIt end) : baseIt(start), endIt(end) {
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
    RefEntity operator->() {
        return it->second.lock();
    }
    RefEntity operator*() {
        return it->second.lock();
    }
    bool operator==(const Iterator& other) {
        return baseIt == other.baseIt;
    }
    bool operator!=(const Iterator& other) {
        return baseIt != other.baseIt;
    }
private:
    EntityMapIt baseIt, endIt;
    EntityIt it;
};

template<>
inline EntityManager::Iterator<Entity> EntityManager::begin() {
    return Iterator<Entity>(map.begin(), map.end());
}
template<>
inline EntityManager::Iterator<Entity>& EntityManager::end() {
    static Iterator<Entity> iter(map.end(), map.end());
    return iter;
}
