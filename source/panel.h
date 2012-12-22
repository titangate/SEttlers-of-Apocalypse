#ifndef PANEL_H
#define PANEL_H
#include "widget.h"
class Panel;
class Panel : public Widget{
public:
    double dt;
    void update(double dt) ;
    void render() ;
    void expand();
    void close();
    double percentsize;
    Panel(Widget * pa,vec2 p,vec2 s,bool vis = true);
    void setPercent(double p);
    
    int state;
    void generateButton(const std::string& s);
};

#endif