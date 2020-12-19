#ifndef MATH_VECTORS_HPP
#define MATH_VECTORS_HPP

#include <math.h>

class Vec2
{   
    public:
        double x,y;
    Vec2 operator *=(Vec2 a);
    Vec2 operator /=(Vec2 a);
    Vec2 operator /=(double a);
    Vec2 operator +=(Vec2 a);
    Vec2 operator -=(double a);
    Vec2 operator -=(Vec2 a);
    Vec2 operator *(Vec2 a);
    Vec2 operator *(double a);
    Vec2 operator /(Vec2 a);
    Vec2 operator /(double a);
    Vec2 operator =(Vec2 a);
    Vec2 operator -(Vec2 a);
    Vec2 operator +(Vec2 a);
    bool operator ==(double a);
    bool operator ==(Vec2 a);
    double length();
    double dest(Vec2 a);
    double angle();
    Vec2 normalized();
};

const Vec2 ZERO_MATH_2D_VECTOR = {0.0,0.0};

#endif