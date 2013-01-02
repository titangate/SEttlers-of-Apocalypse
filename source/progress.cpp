//
//  progress.cpp
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-12-19.
//
//

#include "core.h"
#include "progress.h"
#include "example.h"
#include <sstream>

const double barsize = 16;
const vec2 barscale (0.8,.8);
//const double barspacing = 20;

void ProgressBar::setSize(vec2 size){
    dimension.size = size;
    bar_maxcount = (dimension.size.x-70)/barsize;
    current = 1;
}

void ProgressBar::render(){
    if (current==0) {
        return;
    }
    ExampleRenderer &r = ExampleRenderer::getInstance();
    //current = 1;
    for (int i=0; i<current*bar_maxcount; i++) {
        r.drawImage("bar.png",dimension.pos+vec2(i*barsize,0),0,barscale);
    }
    stringstream s;
    s << (int)(current*100) << "%";
    ExampleRenderer::getInstance().setFont("24");
    r.printf(s.str(), dimension.pos+vec2(dimension.size.x-70,0),IW_2D_FONT_ALIGN_RIGHT,IW_2D_FONT_ALIGN_CENTRE,vec2(70,dimension.size.y));
    ExampleRenderer::getInstance().setFont("arial14");
}

void ProgressBar::update(double dt){
    
}