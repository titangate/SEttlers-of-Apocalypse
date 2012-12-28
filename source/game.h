#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "example.h"
#include "scribbler.h"

class Panel;
class Chip;
struct map_coord {
    int x,y;
};

using namespace std;

class Game {
    vector<Chip*> c;
    vector<Wire*> w;
    Panel * p;
    Chip * highlight;
    AttPanel * ap;
    bool _overlapWithExisted(vec2 pos,vec2 size);
    Widget * base;
public:
    void initDemo(Widget*);
    void update(double dt);
    void render();
    void randomTerrain(vec2 s,unsigned int chipcount);
    void constructCircuits();
    void popWheel(Chip*);
    void releaseWheel();
    void updateAttPanel(vector<AttSubitems>);
    void victory();
    Chip* getSelectedChip();
    Game():p(0),highlight(0){}
    
   // bool construct(Player *,Structure*, map_coord);
    //bool canConstruct(Structure *);
};

#endif