#pragma once
#include "Systems/System.hpp"
#include "Component/Position.hpp"

class PhycicsSystem : public System {
public:
    PhycicsSystem(ComponentManager& manager) : System(manager) {}
    void Update() override {
        for (auto it = manager.begin<Position>(); it != manager.end<Position>(); it++) {
            it->test();
            it->ownerID();
        }
    }
};
