#ifndef CORE_H
#define CORE_H


#include <math.h>
#include <string>
template <class T>
class vec2_t
{
public:
    T   x, y;
    
    vec2_t()
    : x(0.0f), y(0.0f)
    {
    }
    vec2_t(double a,double b)
    : x(a), y(b)
    {
    }
    vec2_t(const vec2_t &v)
    : x(v.x), y(v.y)
    {
    }
    
    inline  vec2_t        operator    -   () const
    {
        return vec2_t(-x, -y);
    }
    inline  vec2_t    &   operator    =   (const vec2_t &v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }
    inline  vec2_t    &   operator    +=  (const vec2_t &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    inline  vec2_t    &   operator    -=  (const vec2_t &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    inline  vec2_t    &   operator    *=  (T scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    inline  vec2_t    &   operator    /=  (T scalar)
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
    inline  vec2_t    &   Normalize       ()
    {
        float length = this->Length();
        x /= length;
        y /= length;
        return *this;
    }
    inline  vec2_t        GetNormalize    () const
    {
        vec2_t res(*this);
        res /= this->Length();
        return res;
    }
    inline  vec2_t    &   ToNull          ()
    {
        x = 0.0f;
        y = 0.0f;
        return *this;
    }
    inline  vec2_t        Left            () const
    {
        return vec2_t(y, -x);
    }
    inline  vec2_t        Right           () const
    {
        return vec2_t(-y, x);
    }
    inline  vec2_t    &   Invert          ()
    {
        x = -x;
        y = -y;
        return *this;
    }
    inline double angleWith(const vec2_t &b){
        return atan2(b.y-this->y, b.x-this->x);
    }
    inline  vec2_t        operator    +   ( const vec2_t &v2)
    {
        return vec2_t(this->x + v2.x, this->y + v2.y);
    }
    
    inline  vec2_t        operator    -   (const vec2_t &v2)
    {
        return vec2_t(this->x - v2.x, this->y - v2.y);
    }
    
    inline  vec2_t        operator    *   (T scalar)
    {
        return vec2_t(this->x * scalar, this->y * scalar);
    }
   
    inline  vec2_t        operator    *   (const vec2_t &v2)
    {
        return vec2_t(this->x * v2.x, this->y * v2.y);
    }
    inline  vec2_t        operator    /   (T scalar)
    {
        return vec2_t(this->x / scalar, this->y / scalar);
    }
    
    inline  vec2_t        operator    /   (const vec2_t &v2)
    {
        return vec2_t(this->x / v2.x, this->y / v2.y);
    }
    inline  float       operator    &   (const vec2_t &v2)
    {
        return this->x * v2.x + this->y * v2.y;
    }
    inline  float       operator    ^   (const vec2_t &v2)
    {
        return this->x * v2.y - this->y * v2.x;
    }
    inline bool operator == (const vec2_t &v2)const{
        return this->x==v2.x && this->y==v2.y;
    }
    
    inline bool operator < (const vec2_t &v2)const{
        return this->x<v2.x ||(this->x==v2.x && this->y<v2.y);
    }

};
template <class T>
 inline  vec2_t<T>        operator    *   (T scalar,const vec2_t<T>& v)
 {
 return vec2_t<T>(scalar * v.x, scalar * v.y);
 }

template <class T>
 inline  vec2_t<T>        operator    /   (T scalar,const vec2_t<T>& v)
 {
 return vec2_t<T>(scalar / v.x, scalar / v.y);
 }
 
 


typedef vec2_t<double> vec2;

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