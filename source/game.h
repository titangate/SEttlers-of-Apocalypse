#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "example.h"
#include "scribbler.h"
#include <set>
//#include "ai.h"

class AI;

class Panel;
class Chip;
struct map_coord {
    int x,y;
};


class GameDelegate {
    
    
public:
    virtual void chipCaptured(Player *,Chip*) = 0;
    virtual void currentSent(Current*) = 0;
    virtual void currentReceived(Current*) = 0;
    virtual void chipUpgradeBegun(Chip*) = 0;
    virtual void chipUpgradeComplete(Chip*) = 0;
};


using namespace std;

class Game :public PlayerDelegate {
    vector<Chip*> c;
    vector<Wire*> w;
    Panel * p;
    Chip * highlight;
    AttPanel * ap;
    bool _overlapWithExisted(vec2 pos,vec2 size);
    Widget * base;
    set<Player*> players;
    set<AI*> ais;
    Player * player;
public:
    void initDemo(Widget*);
    void standardGame(Widget *);
    void update(double dt);
    void render();
    void randomTerrain(vec2 s,unsigned int chipcount);
    void constructCircuits();
    void popWheel(Chip*);
    void releaseWheel();
    void clear();
    void updateAttPanel(vector<AttSubitems>);
    void victory();
    void fail();
    Chip* getSelectedChip();
    Game():p(0),highlight(0){}
    virtual void eliminate(Player* p);
    virtual void acquiredChip(Player*,Chip *){}
    virtual void loseChip(Player*,Chip *){}
    
   // bool construct(Player *,Structure*, map_coord);
    //bool canConstruct(Structure *);
};

#endif