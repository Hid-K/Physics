#ifndef PHISICS_SIMU_CIRCLE_HPP
#define PHISICS_SIMU_CIRCLE_HPP

#include "PhysicsSimuObject.hpp"

class PhysicsSimuObjectCircle : public PhysicsSimuObject
{
private:
    double radius;
public:
    PhysicsSimuObjectCircle(double rad, double weight, Vec2 pos);
    ~PhysicsSimuObjectCircle();

    double getDest(const Vec2 & point);
};


#endif