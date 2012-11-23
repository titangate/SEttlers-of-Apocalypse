#include "anim.h"
#include "s3e.h"

#include <map>
#include <string>
using namespace std;

//typedef  void (*WidgetCallback)(const Widget *, const Event) ;

typedef double (*STYLEFUNC)(double time_e,double start,double interval,double time) ;
map<string, STYLEFUNC> styles;

void Animation::update(double dt){
    time_eplapsed+=dt;
    if (time_eplapsed < time) {
        current = (*styles[style])(time_eplapsed,start,finish-start,time);
        (obj->*setter)(current);
    }
}

double linear(double t,double b, double c, double d){
    return b+c*t/d;}

double quadIn(double t,double b, double c, double d){
    double p = t/d;
    return c*p*p + b;
}


Anim::Anim(){
    styles["linear"] = &linear;
    styles["quadIn"] = &quadIn;
}