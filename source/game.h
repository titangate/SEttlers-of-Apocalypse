#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"
#include "example.h"

struct map_coord {
    int x,y;
};
using namespace std;

class Game {
    vector<Chip*> c;
    vector<Wire*> w;    
public:
    void initDemo(Widget *base);
    void update(double dt);
    void render();
    void randomTerrain();
    void constructCircuits();
    
   // bool construct(Player *,Structure*, map_coord);
    //bool canConstruct(Structure *);
};

#endif