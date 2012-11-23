#ifndef IMAGE_H
#define IMAGE_H
#include "panel.h"
class Image;
class Image: public Panel{
public:
    void pointerPressed(CTouch * c);
    void pointerReleased(CTouch * c);
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