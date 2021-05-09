#include <iostream>
#include <vector>
#include <typeinfo>
#include <typeindex>
#include "Utils/Utils.hpp"
#include "Entity/Manager.hpp"
#include "Component/Manager.hpp"
#include "Systems/Phycics.hpp"

#include "Entity/Animals.hpp"
#include "Component/Position.hpp"
using namespace std;

// Stackoverflow solution
using TypeID2 = uintptr_t;
template<typename T>
TypeID2 getUniqueTypeID() {
    static uint32_t placeHolder;
    return reinterpret_cast<TypeID2>(&placeHolder);
}

int main() {
    cout << getUniqueTypeID<int>() << endl;
    cout << getUniqueTypeID<char>() << endl;
    cout << getUniqueTypeID<double>() << endl;
    cout << getUniqueTypeID<int>() << endl;
    cout << getUniqueTypeID<char>() << endl;
    cout << getUniqueTypeID<double>() << endl;
    cout << typeid(int).hash_code() << endl;
    cout << std::type_index(typeid(int)).hash_code() << endl;
    cout << TypeInfo::get<int>() << endl;
    cout << TypeInfo::get<char>() << endl;
    cout << TypeInfo::get<double>() << endl;
    cout << TypeInfo::get<int>() << endl;
    cout << TypeInfo::get<int>() << endl;
    /*
    vector<int> v {1, 2, 3};
    v.erase(v.begin() + 1);
    cout << v[1] << endl;
    */
    ComponentManager cManager;
    EntityManager manager(cManager);
    
    auto cat = manager.createEntity<Cat>();
    cat->meow();
    auto cat2 = manager.createEntity<Cat>();
    cat2->meow();
    auto cat_2 = manager.getEntity<Cat>(cat->ID());
    cat_2->meow();

    cout << "------" << endl;
    for (auto it = manager.begin<Cat>(); it != manager.end<Cat>(); ++it) {
        cout << "Cat: " << it->ID() << endl;
    }
    cout << "------" << endl;

    manager.createEntity<Dog>();
    manager.createEntity<Floppa>();
    manager.createEntity<Dog>();

    for (auto it = manager.begin(); it != manager.end(); ++it) {
        cout << "Entity: " << it->ID() << endl; 
    }
    for (auto it = cManager.begin(); it != cManager.end(); ++it) {
        cout << "Entity owner: " << it->ownerID() << endl; 
    }

    auto position = cManager.createComponent<Position>(cat->ID(), 1, 2, 3);
    position->test();
    auto position_2 = cManager.getComponent<Position>(cat->ID());
    position_2->test();
    return 0;
}
