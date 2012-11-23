//
//  exampleUI.h
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-02.
//
//

#ifndef __SEofASE__exampleUI__
#define __SEofASE__exampleUI__

#include <iostream>
#include "widget.h"

class UIBase {
public:
    virtual void update(double dt) = 0;
    virtual void render() = 0;
};

class Button1:public Widget{
    
public:
    Button1():Widget(0,vec2(0,0),vec2(100,100)){}
    void update(double dt);
    void render();
    int x,y,w,h;
    double t;
    
    //void setX(double _x){x=(int)_x;}
};


class REDButton :public UIBase{
    
public:
    void update(double dt);
    void render();
    int x,y,w,h;
    double time;
};

#endif /* defined(__SEofASE__exampleUI__) */
