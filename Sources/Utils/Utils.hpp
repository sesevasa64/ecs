#pragma once
#include <cstdint>
#include <memory>
#include <unordered_map>

using TypeID = uint32_t;
using EntityID = TypeID;
using ComponentID = TypeID;

class TypeInfo {
private:
    static TypeID v;
public:
    template<typename T>
    static TypeID get() {
        static TypeID i = v++;
        return i;
    }
};

template<typename T, typename U>
using Map = std::unordered_map<T, U>;

class Entity;
using RefEntity = std::shared_ptr<Entity>;
template<typename T>
using RefDevidedEntity = std::shared_ptr<T>;
using RefWeakEntity = std::weak_ptr<Entity>;
template<typename T>
using RefDevidedWeakEntity = std::weak_ptr<T>;

class Component;
using RefComponent = std::shared_ptr<Component>; 
template<typename T>
using RefDevidedComponent = std::shared_ptr<T>;
using RefWeakComponent = std::weak_ptr<Component>;
template<typename T>
using RefDevidedWeakComponent = std::weak_ptr<T>;
