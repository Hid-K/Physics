#include "PhysicsSimu.hpp"
#include <iostream>
PhysicsSimu::PhysicsSimu(Vec2 environmentViscosity, double simulationTimeStep)
:
environmentViscosity(environmentViscosity),
simulationTimeStep(simulationTimeStep)
{
    this->objestsList = new std::vector<PhysicalCircle>();
};

PhysicsSimu::~PhysicsSimu()
{
    delete this->objestsList;
};

void
PhysicsSimu::simulateTimePeriod(double time)
{
    for(double t = 0; t < time; t += this->simulationTimeStep)
    {
        for(size_t i = 0; i < this->objectsCount(); ++i)
        {
            PhysicalCircle & currObj = *this->getObject(i);
            for(size_t j = 0; j < this->objectsCount(); ++j)
            {
                if(j != i)
                {
                    PhysicalCircle & obj = *this->getObject(j);
                    double collisionDepth = currObj.pos.dest(obj.pos) -
                                            (currObj.radius + obj.radius);
                    if(collisionDepth < 0)
                    {
                        currObj.speed += ((obj.pos - currObj.pos).normalized() - (obj.pos - currObj.pos).normalized()*2) *
                            (obj.weight/currObj.weight)*abs(collisionDepth);
                    };
                }
            };
        };
        for(size_t i = 0; i < this->objectsCount(); ++i)
        {
            PhysicalCircle & currObj = *this->getObject(i);
            currObj.pos += currObj.speed*this->simulationTimeStep;
            Vec2 speedSign = {abs(currObj.speed.x)/currObj.speed.x,abs(currObj.speed.y)/currObj.speed.y};
            currObj.speed -= (this->environmentViscosity * speedSign) * this->simulationTimeStep;
        };
    };
    return;
};

void
PhysicsSimu::addObject(PhysicalCircle obj)
{
    (*this->objestsList).push_back(obj);
    return;
};

void
PhysicsSimu::removeObject(size_t objectNo)
{
    (*this->objestsList).erase((*this->objestsList).begin()+objectNo);
    return;
};

PhysicalCircle *
PhysicsSimu::getObject(size_t objectNo)
{
    return &(*this->objestsList)[objectNo];
};

PhysicalCircle *
PhysicsSimu::getObject(Vec2 point)
{
    for(size_t i = 0; i < this->objectsCount(); ++i)
    {
        if(this->getObject(i)->pos.dest(point) - this->getObject(i)->radius < 0)
        {
            return this->getObject(i);
        };
    };
    return nullptr;
};

size_t
PhysicsSimu::objectsCount()
{
    return (*this->objestsList).size();
};