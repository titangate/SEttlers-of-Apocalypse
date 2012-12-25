#ifndef LABEL_H
#define LABEL_H
#include "widget.h"
class Widget;
class Label : public Widget{
public:
    
    virtual void pointerPressed(CTouch * c);
    virtual void pointerReleased(CTouch * c);
    void registerEvent(std::string event,WidgetCallback) ;
    void update(double dt) ;
    void render() ;
    vec2 getPosition() ;
    void setPosition(vec2) ;
    vec2 getSize() ;
    void setSize(vec2) ;
    void setVisible(bool vis) ;
    void addChild(Widget * child) ;
    void removeFromParent();
    void clearChildren();
    
};

#endif