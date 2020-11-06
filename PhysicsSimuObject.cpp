#include "PhysicsSimuObject.hpp"

Vec2
PhysicsSimuObject::getPos()
{
    return this->pos;
};

void
PhysicsSimuObject::setPos(Vec2 & a)
{
    this->pos = a;
};

double
PhysicsSimuObject::getWeight()
{
    return this->weight;
};

void
PhysicsSimuObject::setWeight(double w)
{
    this->weight = w;
};

Vec2 PhysicsSimuObject::getSpeed()
{
    return this->speed;
};

void PhysicsSimuObject::setSpeed(Vec2 & u)
{
    this->speed = u;
};

double
PhysicsSimuObject::getDest(PhysicsSimuObject & object)
{
    Vec2 collidableObjectVectorDirectionNormal = (object.getPos() - this->getPos()).normalized();

    double objectRayDest = 0.0;
    // double ThisObjectRayDest = 0.0;
    Vec2 rayThisObjectCollidePoint = {0,0};
    Vec2 ray = this->pos;
    for(size_t i = 0; i < collisionRayStepsLimit; ++i)
    {
        ray += collidableObjectVectorDirectionNormal;
        if( this->getDest(ray) >= 0 && rayThisObjectCollidePoint == 0.0 )
            rayThisObjectCollidePoint = ray;
        if( ( objectRayDest = object.getDest(ray) ) <= 0 )
            return this->getDest(ray) - objectRayDest;
    };
};