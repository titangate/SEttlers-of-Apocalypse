#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "resource.h"
#include "structure.h"

using namespace std;
class Chip;
class Player {
    vector<Chip*> chips;
public:
    
    uint8 r,g,b;
    Player():r(125),g(80),b(250){}
};

#endif