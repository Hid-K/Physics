#include "PhysicsSimuObjectCircle.hpp"

PhysicsSimuObjectCircle::PhysicsSimuObjectCircle(double rad, double weight, Vec2 pos)
{
    this->radius = rad;
    this->setPos(pos);
    this->setWeight(weight);
};

double
PhysicsSimuObjectCircle::getDest(const Vec2 & point)
{
    return sqrt(pow(this->getPos().x - point.x, 2) + pow(this->getPos().y - point.y, 2)) - this->radius;
};