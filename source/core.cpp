#ifndef UI_H
#define UI_H


#include <math.h>
#include <string>
#include <sstream>
class vec2
{
public:
    float   x, y;
    
    vec2()
    : x(0.0f), y(0.0f)
    {
    }
    vec2(float _x, float _y)
    : x(_x), y(_y)
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



typedef struct{
    int id;
}Event;

class Widget;

class UI{
public:
    void update(double dt);
    void render();
    void create(std::string s,Widget* parent);
    UI();
protected:
};


#endif