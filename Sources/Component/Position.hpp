#pragma once
#include "Component/Component.hpp"

class Position : public Component {
public:
    Position(double x, double y, double z);
    void test();
private:
    double x, y, z;
};
