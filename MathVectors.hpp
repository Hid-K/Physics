#ifndef MATH_VECTORS_HPP
#define MATH_VECTORS_HPP

#include <math.h>

class Vec2
{   
    public:
        double x,y;
    Vec2 operator *=(Vec2 a);
    Vec2 operator /=(Vec2 a);
    Vec2 operator +=(Vec2 a);
    Vec2 operator *(Vec2 a);
    Vec2 operator /(Vec2 a);
    Vec2 operator =(Vec2 a);
    Vec2 operator -(Vec2 a);
    Vec2 operator +(Vec2 a);
    bool operator ==(double a);
    double length();
    Vec2 normalized();
};

#endif