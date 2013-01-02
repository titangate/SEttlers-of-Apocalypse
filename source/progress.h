//
//  progress.h
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-12-19.
//
//

#ifndef __SEofASE__progress__
#define __SEofASE__progress__

#include "widget.h"

class ProgressBar: public Widget {
    double progress;
    int bar_maxcount;
    double current;
public:
    void update(double dt);
    void render();
    void setProgress(double c){current = c;}
    virtual void setSize(vec2 size);
    ProgressBar(Widget * pa,vec2 p,vec2 s,bool vis = true):Widget(pa,p,s,vis){
        current = 0;
        setSize(s);
    }
};

#endif /* defined(__SEofASE__progress__) */
