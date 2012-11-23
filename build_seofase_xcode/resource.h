//
//  resource.h
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-06.
//
//

#ifndef __SEofASE__resource__
#define __SEofASE__resource__

#include <iostream>
#include <string>
#include "terrain.h"
#include "structure.h"

class Resource {
    int count;
    
public:
    virtual const std::string& getName();
    virtual void update(double dt);
    virtual void render();
    virtual void renderUI();
    virtual void animAcquire(const Terrain& t,const Structure& s);
    int getCount();
    bool spend(int amount);
    
};

#endif /* defined(__SEofASE__resource__) */
