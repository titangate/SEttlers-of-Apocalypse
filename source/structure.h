#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "core.h"
#include "widget.h"
#include "progress.h"
#include "player.h"
#include "example.h"
#include <vector>
#include <map>
class Player;
class Wire;
class Chip;
class Current;

typedef void (*CurrentCallback)(Current* current, Chip* sourcechip, Chip*targetchip, Wire* wire);
using namespace std;

void simpleCurrentCallback(const Current* current, const Chip* sourcechip, const Chip*targetchip, const Wire* wire);
class Chip: public Widget {
    //quad dim;
    double chargeCount;
    double generateRate;
    ProgressBar* pg;
    map<Chip*, Wire*> wires;
public:
    
    virtual void update(double dt);
    virtual void render();
    Chip(Widget * pa,vec2 p,vec2 s,bool vis = true);
    virtual ~Chip(){delete pg;}
    virtual void changeOwner(Player * p){}
    virtual void addWire(Wire *w,Chip* c);
    virtual void receiveCharge(int c){
        chargeCount += c;
    }
    virtual void sendCurrent(Chip *c);
    //virtual void getWireConnectingPoint(Chip* c);
};

class Wire {
    friend class Current;
    vector <vec2> segments;
    vector<Current *> currents;
public:
    Chip* source;
    Chip* target;
    
    Wire(vector<vec2> seg,Chip*s, Chip*t):segments(seg),source(s),target(t){
    }
    ~Wire();
    void setSegments(vector<vec2>seg);
    void update(double dt);
    void render();
    void sendCurrent(double speed,Chip* source,Chip *target,CurrentCallback cb);
    void killCurrent(Current* c);
};

class Current {
    Wire * wire;
    unsigned int currentSeg;
    double currentSpeed;
    bool reverse;
    double distanceOnSeg;
    ParticleSystem * p;
    vec2 pos;
    CurrentCallback cb;
public:
    Current(Wire *w,int currentSegment = 1,double speed = 100,bool reverse = false,CurrentCallback callback = 0):
        wire(w),
        currentSeg(currentSegment),
        currentSpeed(speed),
        reverse(reverse),
        distanceOnSeg(0.0),
        cb(callback)
    {
        p = new ParticleSystem(ExampleRenderer::getInstance().getImage("pulse.png")
                               ,32,32,.5,1200,
                               vec2(1,0),
                               vec2(16,16)
                               );
    }
    
    void update (double dt);
    void render();
};

#endif