#ifndef ATTITEM_H
#define ATTITEM_H

#include "widget.h"
#include "label.h"
#include "structure.h"
#include <map>


class AttPanel:public Widget {
    double secondDiv,thirdDiv,fourthDiv;
    double y;
    map<string, AttSubitems> atts;
public:
    AttPanel(Widget * pa,vec2 p,vec2 s,bool vis = true):Widget(pa,p,s,vis),y(0){
        secondDiv = s.x/3;
        fourthDiv = secondDiv*2;
        thirdDiv = (secondDiv+fourthDiv)/2;
        
    }
    void render();
    void initDemo();
    void clear();
    void addItem(AttSubitems att);
    void constructItems();
};

#endif