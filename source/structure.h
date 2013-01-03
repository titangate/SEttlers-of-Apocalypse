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
class Game;
class Upgrade;

typedef void (*CurrentCallback)(Current* current, Chip* sourcechip, Chip*targetchip, Wire* wire);
using namespace std;

enum attCategory {
    ATT_POSITIVE,
    ATT_NEGATIVE,
    ATT_NEUTRUAL,
    ATT_BASE,
    ATT_DISABLE = ATT_BASE
};

class AttSubitems{
public:
    CIw2DImage * icon;
    string item;
    string current;
    string modifier;
    string after;
    attCategory cat;
    attCategory boost;/*
	AttSubItems( CIw2DImage * icon,
    string item,
    string current,
    string modifier,
    string after,
    attCategory cat,
	attCategory boost):icon(icon),item(item),current(current),modifier(modifier),after(after),cat(cat){
	}*/
};

void simpleCurrentCallback(const Current* current, const Chip* sourcechip, const Chip*targetchip, const Wire* wire);
class Chip: public Widget {
    friend class AI;
    //quad dim;
    
public:
    
    double generateRate;
    double fortification;
    ProgressBar* pg;
    map<Chip*, Wire*> wires;
    vector<Upgrade*> upgrades;
    Player * owner;
    void boostWire();
    double dt;
    Upgrade * currentUpgrade;
    Wire* highlighted;
    
    
    double getDamage(double v);
    Upgrade * getCurrentUpgrade(){
        return currentUpgrade;
    }
    virtual vector<AttSubitems> getAttSubitems();
    double chargeCount;
    Game * game;
    virtual vector<Widget*> getWheelWidgets();
    virtual void update(double dt);
    virtual void render();
    void setSize(vec2);
    Chip(Widget * pa,vec2 p,vec2 s,bool vis = true);
    virtual ~Chip();
    virtual void addWire(Wire *w,Chip* c);
    
    virtual void changeOwner(Player * p);
    Player * getOwner(){return owner;}
    virtual void sendCurrent(Chip *c,int count = -1);
    void pointerPressed(vec2 p, s3ePointerButton key,int id);
    void pointerReleased(vec2 p, s3ePointerButton key,int id);
    void setCurrentUpgrade(Upgrade *);
    //virtual void getWireConnectingPoint(Chip* c);
};

class Wire {
    friend class Current;
    friend class Chip;
    vector <vec2> segments;
    vector<Current *> currents;
    Player * owner;
    uint8 r,g,b;
    double dt;
    unsigned int length;
public:
    Game * game;
    Chip* source;
    Chip* target;
    
    void setR(double _r){r = _r;}
    void setG(double _g){g = _g;}
    void setB(double _b){b = _b;}
    Wire(vector<vec2> seg,Chip*s, Chip*t):segments(seg),source(s),target(t),dt(0){
    }
    ~Wire();
    void setSegments(vector<vec2>seg);
    void update(double dt);
    void render();
    void sendCurrent(double speed,int,Chip* source,Chip *target,CurrentCallback cb);
    void killCurrent(Current* c);
    unsigned int getLength(){return length;}
    virtual void changeOwner(Player * p);
    Player * getOwner(){return owner;}
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
    unsigned int charges;
    Player* owner;
    uint8 r,g,b;
public:
    void setR(double _r){r = _r;}
    void setG(double _g){g = _g;}
    void setB(double _b){b = _b;}
    
    Player * getOwner(){return owner;}
    void changeOwner(Player *p);
    unsigned int getCharges(){return charges;}
    Game * game;
    Current(Wire *w,int currentSegment = 1,double speed = 100,bool reverse = false,CurrentCallback callback = 0,unsigned int c = 0):
        wire(w),
        currentSeg(currentSegment),
        currentSpeed(speed),
        reverse(reverse),
        distanceOnSeg(0.0),
        cb(callback),
        charges(c)
    {
        p = new ParticleSystem(ExampleRenderer::getInstance().getImage("pulse.png")
                               ,32,32,.5,1200,
                               vec2(1,0),
                               vec2(16,16)
                               );
    }
    Chip * getSource(){return wire->source;}
    Chip * getTarget(){return wire->target;}
    double getCurrentSpeed(){return currentSpeed;}
    void update (double dt);
    void render();
};



#endif