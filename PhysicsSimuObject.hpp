#ifndef PHYSICS_SIMU_OBJECT_HPP
#define PHYSICS_SIMU_OBJECT_HPP

#include "MathVectors.hpp"

const static double collisionRayStepCoefficient = 0.01;
const static size_t collisionRayStepsLimit = 1000;

class PhysicsSimuObject
{
    private:
        Vec2 pos;
        Vec2 speed;
        double weight;
    public:
        Vec2 getPos();
        void setPos(Vec2&);

        double getWeight();
        void setWeight(double);

        Vec2 getSpeed();
        void setSpeed(Vec2&);

        /**
         * @return Dest to object
         * 
         * @param object object, to calculate dest to it
        */
        double getDest(PhysicsSimuObject & object);

        /**
         * @return Dest to point
         * 
         * @param point point, to calculate dest to it
        */
        virtual double getDest(const Vec2 & point) = 0;
};

#endif