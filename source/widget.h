#ifndef WIDGET_H
#define WIDGET_H

#include "control.h"
#include <string>
#include "ui.h"
#include <vector>
#include <map>
class Widget;
typedef  void (*WidgetCallback)(const Widget *, const Event) ;
typedef void (Widget::*setter)(double v);
typedef std::vector<Widget*> widgetlist;
typedef std::map< std::string, WidgetCallback > callbacklist;
class Widget{
public:
    widgetlist children;
    quad dimension;
    bool visibility;
    Widget * parent;
    callbacklist cblist;
    uint8 r,g,b,a;
public:
    virtual ~Widget(){}
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
    virtual bool isVisible(){return visibility;}
    virtual void addChild(Widget * child);
    virtual void removeFromParent();
    virtual void clearChildren();
    virtual bool hovered(vec2 p);
    virtual void setR(double _r){r = _r;}
    virtual void setG(double _g){g = _g;}
    virtual void setB(double _b){b = _b;}
    virtual void setOpacity(double _a){a = _a;}
    virtual void setColor(uint8 _r, uint8 _g, uint8 _b, uint8 _a = 255){
        r = _r;
        b = _b;
        g = _g;
        a = _a;
    }
    virtual vec2 getCentre();
    /*virtual void setValue(const std::string& s,double v){
        static std::map<std::string,setter> _t;
        if (_t.empty()) {
            _t["x"] = &Widget::setX;
            _t["y"] = &Widget::setY;
        }
        if (_t.find(s)!=_t.end()) {
            (this->*_t[s])(v);
        }
    }*/
    Widget(Widget * pa,vec2 p,vec2 s,bool vis = true):parent(pa),visibility(vis),r(255),g(255),b(255),a(255){
        setPosition(p);
        setSize(s);
        if(pa)pa->addChild(this);}
};

#endif