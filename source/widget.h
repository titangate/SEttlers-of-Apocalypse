#ifndef WIDGET_H
#define WIDGET_H

#include "control.h"
#include <string>
#include "ui.h"
#include <vector>
#include <map>
class Widget;
typedef  void (*WidgetCallback)(const Widget *, const Event) ;
typedef std::vector<Widget*> widgetlist;
typedef std::map< std::string, WidgetCallback > callbacklist;
class Widget{
public:
    widgetlist children;
    quad dimension;
    bool visibility;
    Widget * parent;
    callbacklist cblist;
public:
    virtual void pointerPressed(vec2 p, s3ePointerButton key,int id);
    virtual void pointerReleased(vec2 p, s3ePointerButton key,int id);
    virtual void registerEvent(std::string event,WidgetCallback);
    virtual void update(double dt);
    virtual void render();
    virtual vec2 getPosition();
    virtual void setPosition(vec2);
    virtual vec2 getSize();
    virtual void setX(double x);
    virtual void setY(double y);
    virtual void setSize(vec2);
    virtual void setVisible(bool vis);
    virtual void addChild(Widget * child);
    virtual void removeFromParent();
    virtual void clearChildren();
    virtual bool hovered(vec2 p);
    Widget(Widget * pa,vec2 p,vec2 s,bool vis = true):parent(pa),dimension(p,s),visibility(vis){}
};

#endif