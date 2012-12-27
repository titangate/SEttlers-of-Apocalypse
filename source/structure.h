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

void simpleCurrentCallback(const Current* current, const Chip* sourcechip, const Chip*targetchip, const Wire* wire);
class Chip: public Widget {
    friend class Upgrade;
    friend class GenerationUpgrade;
    friend class CostItem;

    //quad dim;
    double generateRate;
    ProgressBar* pg;
    map<Chip*, Wire*> wires;
    vector<Upgrade*> upgrades;
    uint8 r,g,b;
    Player * owner;
    void boostWire();
    double dt;
    Wire* highlighted;
public:
    double chargeCount;
    Game * game;
    virtual vector<Widget*> getWheelWidgets();
    virtual void update(double dt);
    virtual void render();
    Chip(Widget * pa,vec2 p,vec2 s,bool vis = true);
    virtual ~Chip();
    virtual void addWire(Wire *w,Chip* c);
    
    virtual void changeOwner(Player * p);
    Player * getOwner(){return owner;}
    virtual void sendCurrent(Chip *c);
    void setR(double _r){r = _r;}
    void setG(double _g){g = _g;}
    void setB(double _b){b = _b;}
    void pointerPressed(vec2 p, s3ePointerButton key,int id);
    void pointerReleased(vec2 p, s3ePointerButton key,int id);
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
    void sendCurrent(double speed,Chip* source,Chip *target,CurrentCallback cb);
    void killCurrent(Current* c);
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
    
    void update (double dt);
    void render();
};


struct AttSubitems{
    CIw2DImage * icon;
    string item;
    string current;
    string modifier;
    string after;
};

class CostItem {
    
    
public:
    virtual void applyUpgrade(Chip*) = 0;
    virtual bool upgradable(Chip*) = 0;
    virtual AttSubitems getAttSubitems() = 0;
};

class ChargeCostItem: public CostItem {
    unsigned int cost;
    virtual struct AttSubitems getAttSubitems(Chip * c){
        struct AttSubitems att = {
            ExampleRenderer::getInstance().getImage("button_glow.png"),
            "Charges",
            toString(c->chargeCount),
            toString(cost),
            toString(c->chargeCount - cost)
        };
        return att;
    }
public:
    void applyUpgrade(Chip* c){
        c->chargeCount -= cost;
    }
    bool upgradable(Chip* c){
        return c->chargeCount >= cost;
    }
};


class Upgrade {
protected:
    unsigned int lvl;
    vector<CostItem*> costs[10];
    unsigned int maxlvl;
    Chip * c;
    double progress;
public:
    //virtual unsigned int cost();
    virtual CIw2DImage* getIcon(){return 0;}
    virtual double getProgress(){return progress;};
    virtual void applyUpgrade(unsigned int level){
        for (vector<CostItem*>::iterator i=costs[level].begin(); i!=costs[level].end(); i++) {
            (*i)->applyUpgrade(c);
        }
        lvl = level;
    }
    virtual bool upgradable(unsigned int level){
        for (vector<CostItem*>::iterator i=costs[level].begin(); i!=costs[level].end(); i++) {
            if (!(*i)->upgradable(c))return false;
        }
        return true;
    }
    virtual vector<AttSubitems> getAttSubitems(unsigned int level,vector<AttSubitems> att = vector<AttSubitems>()){
        for (vector<CostItem*>::iterator i=costs[level].begin(); i!=costs[level].end(); i++) {
            att.push_back((*i)->getAttSubitems());
        }
        return att;
    }
    void addCost(unsigned int level,CostItem* c){
        costs[level].push_back(c);
    }
    unsigned int getLevel(){
        return lvl;
    }
    Upgrade(Chip * chip,unsigned int level = 0,unsigned int maxlevel = 10):c(chip),lvl(level),maxlvl(maxlevel),progress(0){}
};


class GenerationUpgrade :public Upgrade {
    double genRateModifier;
public:
    CIw2DImage* getIcon(){return ExampleRenderer::getInstance().getImage("generation.png");}
    void applyUpgrade(unsigned int level){
        Upgrade::applyUpgrade(level);
        c->generateRate -= genRateModifier;
        vec2 s = c->dimension.size;
        genRateModifier = level * s.x*s.y/20000;
        c->generateRate += genRateModifier;
    }
    virtual vector<AttSubitems> getAttSubitems(unsigned int level){
        vec2 s = c->dimension.size;
        struct AttSubitems att = {
            getIcon(),
            "Generation",
            toString(c->generateRate),
            toString(s.x*s.y/20000),
            toString(c->generateRate+s.x*s.y/20000)
        };
        vector<AttSubitems> t;
        t.push_back(att);
        return Upgrade::getAttSubitems(level,t);
    }
GenerationUpgrade(Chip * chip,unsigned int level = 0,unsigned int maxlevel = 10):Upgrade(chip,level,maxlevel),genRateModifier(0){}
};

#endif