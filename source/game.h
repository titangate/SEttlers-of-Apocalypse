#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"

struct map_coord {
    int x,y;
};
using namespace std;

class Game {
    vector<Player*> player;
    
public:
    void update(double dt);
    void render();
    void randomTerrain();
    Player * checkVictory();
    
    bool construct(Player *,Structure*, map_coord);
    bool canConstruct(Structure *);
};

#endif