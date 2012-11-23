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

class UIBase {
public:
    virtual void update(double dt) = 0;
    virtual void render() = 0;
};

class Button :public UIBase{
    
public:
    void update(double dt);
    void render();
    int x,y,w,h;
};


class REDButton :public UIBase{
    
public:
    void update(double dt);
    void render();
    int x,y,w,h;
    double time;
};

#endif /* defined(__SEofASE__exampleUI__) */
