#ifndef BUTTON_H
#define BUTTON_H
#include "panel.h"
class Button:public Widget{
public:
    void pointerReleased(vec2 p, s3ePointerButton key,int id);
    void render() ;
    /*
    void pointerPressed(CTouch * c);
    void registerEvent(std::string event,WidgetCallback) ;
    void update(double dt) ;
    vec2 getPosition() ;
    void setPosition(vec2) ;
    vec2 getSize() ;
    void setSize(vec2) ;
    void setVisible(bool vis) ;
    void addChild(Widget * child) ;
    void removeFromParent();
    void clearChildren();*/
    
};

#endif