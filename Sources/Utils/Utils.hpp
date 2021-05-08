#pragma once
#include <cstdint>
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
