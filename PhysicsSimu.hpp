#ifndef PHYSICS_SIMU_HPP
#define PHYSICS_SIMU_HPP
#include "MathVectors.hpp"
#include <vector>
#include <stddef.h>

struct RGB
{
    char r,g,b;
};

struct PhysicalCircle
{
    double radius;
    double weight;
    Vec2 pos;
    Vec2 speed;
    RGB color;
};

class PhysicsSimu
{
private:
    std::vector<PhysicalCircle> * objestsList;
    Vec2 environmentViscosity;
    double simulationTimeStep;
public:
    PhysicsSimu(Vec2 environmentViscosity, double simulationTimeStep);
    ~PhysicsSimu();

    void simulateTimePeriod(double time);
    void addObject(PhysicalCircle obj);
    void removeObject(size_t objectNo);
    /**
     * @returns Object number objectNo
    **/
    PhysicalCircle * getObject(size_t objectNo);

    /**
     * @returns Object, colliding with point
    **/
    PhysicalCircle * getObject(Vec2 point);

    size_t objectsCount();
};

#endif