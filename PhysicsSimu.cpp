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
                        circlesCollisionSpeedCalc(currObj, obj);
                        circlesCollisionSpeedCalc(obj, currObj);
                        currObj.speed += (obj.pos - currObj.pos) * collisionDepth;
                        obj.speed += (currObj.pos - obj.pos) * collisionDepth;
                        // std::cout<<currObj.speed.x<<'\n';
                        // std::cout<<currObj.speed.y<<'\n';
                        // std::cout<<obj.speed.x<<'\n';
                        // std::cout<<obj.speed.y<<'\n'<<'\n';
                    } else
                    {
                        /*Universal gravitation ( UNSTABLE!!!! )*/
                        // currObj.speed += ( ( ((currObj.pos - obj.pos).normalized() - (currObj.pos - obj.pos).normalized()*2) /
                        //              this->environmentViscosity ) *
                        //              ((currObj.mass * obj.mass) / collisionDepth * collisionDepth) ) / 1000000000000;
                    };
                }
            };
        };
        for(size_t i = 0; i < this->objectsCount(); ++i)
        {
            PhysicalCircle & currObj = *this->getObject(i);
            if(currObj.mass < __PHYSICSSIMU_MASS_MAX__)
            {
                currObj.pos += currObj.speed*this->simulationTimeStep;
                Vec2 speedSign = {0,0};
                if(currObj.speed.x != 0)
                {
                    speedSign.x = abs(currObj.speed.x)/currObj.speed.x;
                };
                if(currObj.speed.y != 0)
                {
                    speedSign.y = abs(currObj.speed.y)/currObj.speed.y;
                };

                currObj.speed -= (this->environmentViscosity * speedSign) * this->simulationTimeStep;
            } else
            {
                // currObj.speed = {0,0};
            };
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

void circlesCollisionSpeedCalc(PhysicalCircle & obj, PhysicalCircle & currObj)
{
    Vec2 collisionNorm = (obj.pos - currObj.pos);

    double touchAngle        =  collisionNorm.angle();
    double currObjSpeedAngle =  currObj.speed.angle();
    double objSpeedAngle     =  obj.speed.angle();

    const double currObjSpeedLen = currObj.speed.length();

    const double speedModule = ( currObjSpeedLen * cos(currObjSpeedAngle - touchAngle) * (currObj.mass - obj.mass) + 
                                 2 * obj.mass * obj.speed.length() * cos(objSpeedAngle - touchAngle) )
                                 /
                                 (currObj.mass + obj.mass);

    currObj.speed.x = speedModule
                    *
                    cos(touchAngle) +
                    currObjSpeedLen * sin(currObjSpeedAngle - touchAngle) * cos(touchAngle + M_PI_2)
                    ;

    currObj.speed.y = speedModule
                    *
                    sin(touchAngle) +
                    currObjSpeedLen * sin(currObjSpeedAngle - touchAngle) * sin(touchAngle + M_PI_2)
                    ;

    // currObj.speed /= 2;
};