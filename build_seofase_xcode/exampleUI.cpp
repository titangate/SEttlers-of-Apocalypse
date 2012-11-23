//
//  exampleUI.cpp
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-02.
//
//

#include "exampleUI.h"
#include "example.h"
#include <math.h>

ExampleRenderer renderer;

void Button::update(double dt){
    
}

void Button::render(){
    renderer.drawBlackSquare(x, y, w, h);
}


void REDButton::update(double dt){
    time += (dt/1000);
}

void REDButton::render(){
    renderer.drawRedSquare(x, y, (cos(time)+1)*w, (cos(time)+1)*h);
}

