#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include <string>
//#include "resource.h"
#include "structure.h"
class Chip;
class Player;
class PlayerDelegate {
    
    
public:
    virtual void eliminate(Player*) = 0;
    virtual void acquiredChip(Player*,Chip *)=0;
    virtual void loseChip(Player*,Chip *)=0;
    //virtual void sendCurrent
};

class Player {
    std::set<Chip*> chips;
    PlayerDelegate * del;
public:
    bool eliminated(){return chips.empty();}
    void acquireChip(Chip*);
    void loseChip(Chip*);
    uint8 r,g,b;
    Player():r(125),g(80),b(250),del(0){}
    void setDelegate(PlayerDelegate* d){del = d;}
};

#endif