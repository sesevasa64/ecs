#pragma once
#include "Component/Component.hpp"

class Position : public Component {
public:
    Position(EntityID ownerID, double x, double y, double z);
    void test();
private:
    double x, y, z;
};
