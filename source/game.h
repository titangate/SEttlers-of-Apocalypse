#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "example.h"

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
public:
    void initDemo(Widget *base);
    void update(double dt);
    void render();
    void randomTerrain();
    void constructCircuits();
    void popWheel(Chip*);
    void releaseWheel();
    Chip* getSelectedChip();
    Game():p(0),highlight(0){}
    
   // bool construct(Player *,Structure*, map_coord);
    //bool canConstruct(Structure *);
};

#endif