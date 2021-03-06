#include "MathVectors.hpp"

Vec2
Vec2::operator *=(Vec2 a)
{
    Vec2 res;
    res.x = this->x *= a.x;
    res.y = this->y *= a.y;
    return res;
};

Vec2
Vec2::operator /=(Vec2 a)
{
    Vec2 res;
    res.x = this->x /= a.x;
    res.y = this->y /= a.y;
    return res;
};

Vec2
Vec2::operator /=(double a)
{
    Vec2 res;
    res.x = this->x /= a;
    res.y = this->y /= a;
    return res;
};

Vec2
Vec2::operator /(double a)
{
    Vec2 res;
    res.x = this->x / a;
    res.y = this->y / a;
    return res;
};

Vec2
Vec2::operator +=(Vec2 a)
{
    Vec2 res;
    res.x = this->x += a.x;
    res.y = this->y += a.y;
    return res;
};

Vec2 
Vec2::operator -=(double a)
{
    return {this->x -= a, this->y -= a};
};

Vec2 
Vec2::operator -=(Vec2 a)
{
    return {this->x -= a.x, this->y -= a.y};
};

Vec2
Vec2::operator *(Vec2 a)
{
    Vec2 res;
    res.x = this->x * a.x;
    res.y = this->y * a.y;
    return res;
};

Vec2
Vec2::operator *(double a)
{
    return {this->x *a, this->y * a};
};

Vec2
Vec2::operator /(Vec2 a)
{
    Vec2 res;
    res.x = this->x / a.x;
    res.y = this->y / a.y;
    return res;
};

Vec2
Vec2::operator =(Vec2 a)
{
    this->x = a.x;
    this->y = a.y;
    return *this;
};

Vec2
Vec2::operator -(const Vec2 a)
{
    Vec2 res;
    res.x = this->x - a.x;
    res.y = this->y - a.y;
    return res;
};

Vec2
Vec2::operator +(Vec2 a)
{
    Vec2 res;
    res.x = this->x + a.x;
    res.y = this->y + a.y;
    return res;
};

bool
Vec2::operator ==(double a)
{
    if(this->x == a && this->y == a) return true;
    else return false;
};

bool
Vec2::operator ==(Vec2 a)
{
    if(this->x == a.x && this->y == a.y) return true;
    else return false;
};

double
Vec2::length()
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
};

double
Vec2::dest(Vec2 a)
{
    return sqrt(pow(a.x - this->x, 2) + pow(a.y - this->y, 2));
};

double
Vec2::angle()
{
    double angle = abs(atan(this->y / this->x));
    if(isnan(angle))
    {
        if(y == 0)
        {
            angle = 0;
        } else if(y > 0)
        {
            angle = M_PI_4;
        } else if(y < 0)
        {
            angle = M_PI + M_PI_4;
        };
    } else
    {
        if(angle == 0 && y == 0)
        {
            if(x > 0)
            {
                angle = 0;
            } else if(x < 0)
            {
                angle = M_PI;
            };
        } else
        {
            if(x < 0 && y > 0)
            {
                angle = (M_PI - angle);
            } else if(x < 0 && y < 0)
            {
                angle = M_PI + angle;
            } else if(x > 0 && y < 0)
            {
                angle = M_PI + (M_PI - angle);
            };
        };
    };
    return angle;
};

Vec2
Vec2::normalized()
{
    double len = this->length();
    Vec2 norm;
    norm.x = this->x / len;
    norm.y = this->y / len;
    return norm;
};