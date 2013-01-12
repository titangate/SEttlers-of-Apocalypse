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
	Current* current;
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
    virtual void update() = 0;
public:
    AI(Game* g,Player* p);
	virtual ~AI();
	virtual void update(double dt) {update();}
	virtual void chipCaptured(Player *,Chip*){update();}
    virtual void currentSent(Current*);
    virtual void currentReceived(Current*);
	virtual void chipUpgradeBegun(Chip*){update();}
	virtual void chipUpgradeComplete(Chip*){update();}

	SimpleChip predict(Chip*, double t); // time in seconds from now
};

class SimpleAI : public AI {

public:
	SimpleAI(Game* g, Player* p):AI(g,p){}
	~SimpleAI();
	void update(double dt);
};

#endif