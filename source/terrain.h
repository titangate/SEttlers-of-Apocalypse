#ifndef TERRAIN_H
#define TERRAIN_H
#include <string>
class Terrain {
    int id;
    
public:
    
    virtual const std::string & getName();
    virtual void render();
    virtual void update(double dt);
    virtual void setPosition(int x,int y);
    
};

#endif