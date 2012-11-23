#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "resource.h"
#include "structure.h"

using namespace std;

class Player {
    vector<Resource*> resource;
    vector<Structure*> structure;
    
public:
    void update(double dt);
    void render();
    
};

#endif