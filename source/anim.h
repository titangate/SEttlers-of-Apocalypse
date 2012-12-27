#ifndef ANIMATION_H
#define ANIMATION_H
#include "widget.h"
#include <string>
#include <vector>

template <class T>
class Anim;
using namespace std;

typedef double (*STYLEFUNC)(double time_e,double start,double interval,double time) ;
extern map<string, STYLEFUNC> stylefs;
double linear(double t,double b, double c, double d);
double quadIn(double t,double b, double c, double d);
double quadOut(double t,double b, double c, double d);
template <class T>
class Animation{
public:
    void (T::*setter)(double value);
    T* obj;
    double start,finish;
    double time,delay,current;
    double time_eplapsed;
    std::string style;
    Animation(void (T::*_setter)(double value),T* _obj,
              double _start,double _finish,double _time,
              const std::string& _style):
    setter(_setter),obj(_obj),
        start(_start),finish(_finish),time(_time),style(_style),current(_start),time_eplapsed(0)
    {}
    bool update (double dt){
        time_eplapsed+=dt;
        if (time_eplapsed < time) {
            current = (*stylefs[style])(time_eplapsed,start,finish-start,time);
            (obj->*setter)(current);
        }
        else{
            (obj->*setter)(finish);
            //vector < Animation<T> > & anim = Anim<T>::getInstance().anims;
            return true;
            //anim.erase(find(anim.begin(), anim.end(), *this));
        }
        return false;
    }
    
};

template <class T>
class Anim{
    friend class Animation<T>;
protected:
    vector<Animation<T> > anims;
public:
    static Anim & getInstance(){
        static Anim instance;
        
        return instance;
    }
    void animate(T * w,void (T::*_setter)(double value),double start,double finish,double time,string style = "linear"){
        anims.push_back(Animation<T>(_setter,w,start,finish,time,style));
    }
    void update(double dt){
        for (unsigned int i=0; i<anims.size(); i++) {
            if(anims[i].update(dt)) anims.erase(anims.begin()+i);
        }
    }

    Anim(){
        stylefs["linear"] = &linear;
        stylefs["quadIn"] = &quadIn;
        stylefs["quadOut"] = &quadIn;
    }
    
};

#endif