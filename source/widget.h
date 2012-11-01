#ifndef WIDGET_H
#define WIDGET_H

#include "control.h"
#include <string>
#include "ui.h"
class Widget;
typedef  void (*WidgetCallback)(const Widget *, const Event *) ;
class Widget{
public:
    virtual void pointerPressed(CTouch * c) = 0;
    virtual void pointerReleased(CTouch * c) = 0;
    virtual void registerEvent(std::string event,WidgetCallback) = 0;
    virtual void update(double dt) = 0;
    virtual void render() = 0;
    virtual vec2 getPosition() = 0;
    virtual void setPosition(vec2) = 0;
    virtual vec2 getSize() = 0;
    virtual void setSize(vec2) = 0;
    virtual void setVisible(bool vis) = 0;
    virtual void addChild(Widget * child) = 0;
    virtual void removeFromParent() = 0;
    virtual void clearChildren() = 0;
};

#endif