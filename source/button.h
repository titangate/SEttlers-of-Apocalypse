#ifndef BUTTON_H
#define BUTTON_H
#include "panel.h"
#include "Iw2D.h"
#include <string>
using namespace std;
class Button:public Widget{
    bool active;
public:
    void pointerReleased(vec2 p, s3ePointerButton key,int id);
    void render() ;
    void update (double dt);
    void * userdata;
    void setSize(vec2);
    void setImage(CIw2DImage* img){image = img;}
    /*
    void pointerPressed(CTouch * c);
    void registerEvent(std::string event,WidgetCallback) ;
    void update(double dt) ;
    vec2 getPosition() ;
    void setPosition(vec2) ;
    vec2 getSize() ;
     ;
    void setVisible(bool vis) ;
    void addChild(Widget * child) ;
    void removeFromParent();
    void clearChildren();*/
    void setText(const string & s){text = s;}
    void setActive(bool a){active = a;}
    Button(Widget * pa,vec2 p,vec2 s,bool vis = true);
    ~Button();
    double dt;
    string text;
    CIw2DImage* image;
};

#endif