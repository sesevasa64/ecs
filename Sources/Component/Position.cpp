#include "Component/Position.hpp"
#include <iostream>
using namespace std;

Position::Position(double x, double y, double z) 
: x(x), y(y), z(z) {}

void Position::test() { 
    cout << x << " " << y << " " << z << endl; 
}
