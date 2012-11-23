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

using namespace std;


class ExampleRenderer{
public:
    CIw2DImage * getImage(const string& s);
    ExampleRenderer();
    void render();
    void init();
    void terminate();
    void drawImage(CIw2DImage * image,vec2 pos,double angle,vec2 scale = vec2(1,1),
                   vec2 origin=vec2(0,0));
    void drawImage(const string &s,vec2 pos,double angle,vec2 scale = vec2(1,1),
                   vec2 origin=vec2(0,0));
    void drawImageQ(CIw2DImage * image,quad q,vec2 pos,double angle,vec2 scale = vec2(1,1),
                    vec2 origin=vec2(0,0));
    void printf(const string &s, vec2 pos,CIw2DFontAlign horzAlign = IW_2D_FONT_ALIGN_LEFT,CIw2DFontAlign vertAlign = IW_2D_FONT_ALIGN_TOP,vec2 size=vec2(1000,1000));
    void setColor(uint8 r,uint8 g,uint8 b,uint8 a){
        CIwColour c;
        c.Set(r,g,b,a);
        Iw2DSetColour(c);}
    void resetColor(){Iw2DSetColour(0xffffffff);}
    void push();
    void pop();
    
protected:
    map<string, CIw2DImage *> _images;
    stack<CIwMat2D> _matrixStack;
};
#endif /* defined(__SEofASE__example__) */
