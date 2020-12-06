#ifndef PHYSICS_SIMU_HPP
#define PHYSICS_SIMU_HPP
#include "MathVectors.hpp"
#include <vector>
#include <stddef.h>
#include <limits.h>

#define __PHYSICSSIMU_MASS_MAX__ std::numeric_limits<double>::max()

struct RGB
{
    char r,g,b;
};

struct PhysicalCircle
{
    double radius;
    double mass;
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