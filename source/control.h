#ifndef CONTROL_H
#define CONTROL_H
#include "core.h"
#include "ui.h"
#include "s3e.h"

class controlDelegate {
    
    
public:
    virtual void pointerPressed (double x,double y, s3ePointerButton key,int id){}
    virtual void pointerReleased (double x,double y, s3ePointerButton key,int id){}
    virtual void pointerMotion( double x, double y, int id){}
};


struct CTouch
{
    int32 x; // position x
    int32 y; // position y
    bool active; // is touch active (currently down)
    int32 id; // touch's unique identifier
};

class Control {
protected:
    void update(double dt);
    Control();
    controlDelegate * delegate;
public:
    static Control & getInstance(){
            static Control instance;
            return instance;
    }
    void registerDelegate(controlDelegate * del);
    void unregisterDelegate();
    void pointerPressed (double x,double y, s3ePointerButton key,int id);
    void pointerReleased (double x,double y, s3ePointerButton key,int id);
    void pointerMotion( double x, double y, int id);
    CTouch* getPointer(int id);
};
#endif