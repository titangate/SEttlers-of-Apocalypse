#ifndef CORE_H
#define CORE_H


#include <math.h>
#include <string>
class vec2
{
public:
    float   x, y;
    
    vec2()
    : x(0.0f), y(0.0f)
    {
    }
    vec2(double a,double b)
    : x(a), y(b)
    {
    }
    vec2(const vec2 &v)
    : x(v.x), y(v.y)
    {
    }
    
    inline  vec2        operator    -   () const
    {
        return vec2(-x, -y);
    }
    inline  vec2    &   operator    =   (const vec2 &v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }
    inline  vec2    &   operator    +=  (const vec2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    inline  vec2    &   operator    -=  (const vec2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    inline  vec2    &   operator    *=  (float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    inline  vec2    &   operator    /=  (float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    inline  float       Length          () const
    {
        return sqrt(x*x + y*y);
    }
    inline  float       QuadLength      () const
    {
        return sqrt(x) + sqrt(y);
    }
    inline  vec2    &   Normalize       ()
    {
        float length = this->Length();
        x /= length;
        y /= length;
        return *this;
    }
    inline  vec2        GetNormalize    () const
    {
        vec2 res(*this);
        res /= this->Length();
        return res;
    }
    inline  vec2    &   ToNull          ()
    {
        x = 0.0f;
        y = 0.0f;
        return *this;
    }
    inline  vec2        Left            () const
    {
        return vec2(y, -x);
    }
    inline  vec2        Right           () const
    {
        return vec2(-y, x);
    }
    inline  vec2    &   Invert          ()
    {
        x = -x;
        y = -y;
        return *this;
    }
    inline double angleWith(const vec2 &b){
        return atan2(b.y-this->y, b.x-this->x);
    }
};

inline  vec2        operator    +   (const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x + v2.x, v1.y + v2.y);
}
inline  vec2        operator    -   (const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x - v2.x, v1.y - v2.y);
}
inline  vec2        operator    *   (const vec2 &v, float scalar)
{
    return vec2(v.x * scalar, v.y * scalar);
}
inline  vec2        operator    *   (float scalar, const vec2 &v)
{
    return vec2(scalar * v.x, scalar * v.y);
}
inline  vec2        operator    *   (const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x * v2.x, v1.y * v2.y);
}
inline  vec2        operator    /   (const vec2 &v, float scalar)
{
    return vec2(v.x / scalar, v.y / scalar);
}
inline  vec2        operator    /   (float scalar, const vec2 &v)
{
    return vec2(scalar / v.x, scalar / v.y);
}
inline  vec2        operator    /   (const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.x / v2.x, v1.y / v2.y);
}
inline  float       operator    &   (const vec2 &v1, const vec2 &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
inline  float       operator    ^   (const vec2 &v1, const vec2 &v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

class quad{
public:
    vec2 pos;
    vec2 size;
    bool contain(const vec2& p){
        return p.x-pos.x >= 0 && p.x-pos.x <= size.x &&
        p.y-pos.y >= 0 && p.y-pos.y <= size.y;
    }
    quad():pos(0,0),size(0,0){
        
    }
    quad(const vec2& p,const vec2& s):pos(p),size(s){}
};


typedef struct{
    int id;
}Event;


#endif