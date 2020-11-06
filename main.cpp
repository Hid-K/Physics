#include <SDL.h>
#include <iostream>
#include "PhysicsSimu.hpp"
#include "PhysicsSimuObjectCircle.hpp"
int main()
{
    PhysicsSimuObjectCircle circle(10.0, 2.0, {10.0,10.0});
    PhysicsSimu simulation;
    simulation.addObject(circle);
    Vec2 pos {19.0,19.0};
    circle.setPos(pos);
    simulation.addObject(circle);
    simulation.step(2);
    return 0;
};