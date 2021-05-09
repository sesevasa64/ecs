#include "Component/Position.hpp"
#include <iostream>
using namespace std;

Position::Position(EntityID ownerID, double x, double y, double z) 
: Component(ownerID), x(x), y(y), z(z) {}

void Position::test() { 
    cout << x << " " << y << " " << z << endl; 
}
