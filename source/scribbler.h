#ifndef ATTITEM_H
#define ATTITEM_H

#include "widget.h"
#include "label.h"


class AttPanel:public Widget {
    
    
public:
    AttPanel(Widget * pa,vec2 p,vec2 s,bool vis = true):Widget(pa,p,s,vis){
        
        
    }
    void render();
    void initDemo();
};

#endif