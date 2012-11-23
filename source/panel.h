#ifndef PANEL_H
#define PANEL_H
#include "widget.h"
class Panel;
class Panel : public Widget{
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