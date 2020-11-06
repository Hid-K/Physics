#ifndef PHYSICS_SIM_HPP
#define PHYSICS_SIM_HPP

#include "MathVectors.hpp"
#include "PhysicsSimuObject.hpp"
#include <vector>
#include <iostream>

class PhysicsSimu
{
    private:
        std::vector<PhysicsSimuObject> * objectsList;
    public:
    PhysicsSimu();
    ~PhysicsSimu();

    void step();
    void step(size_t t);

    void addObject(PhysicsSimuObject&);
};

#endif