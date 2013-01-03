#ifndef AI_H
#define AI_H

#include "game.h"
#include <vector>
#include <map>
#include <set>

using namespace std;

class SimpleChip {
public:
    double generateRate;
    double fortification;
    //map<Chip*, Wire*> wires;
    vector<Upgrade*> upgrades;
    Player * owner;
    Upgrade * currentUpgrade;
    double chargeCount;
    Game * game;
    
    SimpleChip(Chip* c);
};

class SimpleCurrent {
public:
    Player* owner;
    unsigned int charges;
    Chip* src;
    Chip* dest;
    double distanceToTarget;
    double currentSpeed;
    SimpleCurrent(Current*); // use only in currentSent
    double estTimeArrival();
};

class AI: public GameDelegate {
    Game * game;
    Player * me;
    Player * neutral;
    set<Player*> enemies;
    map<Player*, set<SimpleCurrent*> > currents;
    
public:
    AI(Game* g,Player* p):game(g),me(p){}
    virtual void update() = 0;
    SimpleChip predict(Chip*, double t); // time in seconds from now
};

class SimpleAI : public AI {

public:
    virtual void update();
    virtual void chipCaptured(Player *,Chip*);
    virtual void currentSent(Current*);
    virtual void currentReceived(Current*);
    virtual void chipUpgraded(Chip*);
    virtual void chipUpgradeComplete(Chip*);
};

#endif