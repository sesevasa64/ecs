#pragma once
#include <cstdint>

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
