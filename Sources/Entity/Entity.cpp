#include "Entity.hpp"
#include <iostream>
using namespace std;

Entity::Entity(EntityID id, ComponentManager& manager)
: id(id), manager(manager) {}
