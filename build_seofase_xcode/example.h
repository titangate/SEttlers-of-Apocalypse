//
//  example.h
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-02.
//
//

#ifndef __SEofASE__example__
#define __SEofASE__example__

#include <iostream>


class ExampleRenderer{
public:
    void update(double dt);
    void render();
    ExampleRenderer();
    void drawBlackSquare(int x0, int y0, int w, int h);
    void drawRedSquare(int x0, int y0, int w, int h);
    void terminate();
protected:
    
};
#endif /* defined(__SEofASE__example__) */
