//
//  example.h
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-02.
//
//

#ifndef __SEofASE__example__
#define __SEofASE__example__

#include <iostream>
#include <string>
#include <map>
#include "Iw2D.h"
#include <core.h>
#include <stack>
#include <deque>


using namespace std;
class Particle {
    friend class ParticleSystem;
    vec2 pos;
    //vec2 scale;
    double life;
public:
    Particle(vec2 p,double l):pos(p),life(l){}
};

class ParticleSystem {
    deque<Particle> particles;
    int count;
    int max_count;
    bool started;
    int emissionrate;
    double particlelife;
    double life;
    double systemlife;
    double dt;
    vec2 deltasize;
    vec2 origin;
    CIw2DImage* image;
    void emit();
    
    vec2 pos;
public:
    void start(){life = systemlife;}
    void stop(){life = 0;}
    void update(double dt);
    void render();
    void setPosition(vec2 p){pos = p;}
    ParticleSystem(CIw2DImage* img,
                   int maxcount = 32,
                   int emis = 16,
                   double particle_life = .5,
                   double system_life = 1200,
                   vec2 delta_size = vec2(1,1),
                   vec2 orig = vec2(0,0)
                   ):
    image(img),particlelife(particle_life),systemlife(system_life),deltasize(delta_size),origin(orig),life(system_life),emissionrate(emis),dt(0),max_count(maxcount)
    {}
};

class ExampleRenderer{
public:
    CIw2DImage * getImage(const string& s);
    CIw2DFont * getFont(const string& s);
    ExampleRenderer();
    void render();
    void init();
    void terminate();
    void drawImage(CIw2DImage * image,vec2 pos,double angle,vec2 scale = vec2(1,1),
                   vec2 origin=vec2(0,0));
    void drawImage(const string &s,vec2 pos,double angle,vec2 scale = vec2(1,1),
                   vec2 origin=vec2(0,0));
    void drawImageQ(CIw2DImage * image,quad q,vec2 pos,double angle,vec2 scale = vec2(1,1),vec2 origin=vec2(0,0));
    void drawImageQ(const string &s,quad q,vec2 pos,double angle,vec2 scale = vec2(1,1),vec2 origin=vec2(0,0));
    void printf(const string &s, vec2 pos,CIw2DFontAlign horzAlign = IW_2D_FONT_ALIGN_LEFT,CIw2DFontAlign vertAlign = IW_2D_FONT_ALIGN_TOP,vec2 size=vec2(1000,1000));
    void setColor(uint8 r,uint8 g,uint8 b,uint8 a){
        CIwColour c;
        c.Set(r,g,b,a);
        Iw2DSetColour(c);}
    void resetColor(){Iw2DSetColour(0xffffffff);}
    void push();
    void pop();
    
    void scale(vec2 scale);
    void rotate(double angle);
    void translate(vec2 pos);
    void setFont(const string& s);
    
    // drawing primitives
    //void line(
    
    static ExampleRenderer & getInstance(){
        static ExampleRenderer instance;
        return instance;
    }
    
protected:
    map<string, CIw2DImage *> _images;
    map<string, CIw2DFont *> _fonts;
    stack<CIwMat2D> _matrixStack;
    
};
#endif /* defined(__SEofASE__example__) */
