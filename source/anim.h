#ifndef ANIMATION_H
#define ANIMATION_H
#include "widget.h"
#include <string>
#include <vector>
using namespace std;
class Animation{
public:
    void (Widget::*setter)(double value);
    Widget* obj;
    double start,finish;
    double time,delay,current;
    double time_eplapsed;
    std::string style;
    Animation(void (Widget::*_setter)(double value),Widget* _obj,
              double _start,double _finish,double _time,
              const std::string& _style):
    setter(_setter),obj(_obj),
        start(_start),finish(_finish),time(_time),style(_style),current(_start),time_eplapsed(0)
    {}
    void update (double dt);
    
};

class Anim{
public:
    static Anim & getInstance(){
        static Anim instance;
        
        return instance;
    }
    void animate(Widget * w,void (Widget::*_setter)(double value),double start,double finish,double time,string style = "linear"){
        anims.push_back(Animation(_setter,w,start,finish,time,style));
    }
    void update(double dt){
        for (int i=0; i<anims.size(); i++) {
            anims[i].update(dt);
        }
    }
protected:
    vector<Animation> anims;
    Anim();
    
};

#endif