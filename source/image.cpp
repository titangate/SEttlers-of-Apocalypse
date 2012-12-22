#include "image.h"
#include "example.h"
#include <math.h>
#include "Iw2D.h"

void Image::render(){
    
    ExampleRenderer::getInstance().drawImage(imageName, dimension.pos+vec2(dt*50-64,-16), 0,vec2(1,1));
    
}

void Image::update(double t){
        dt+= t;
}

void Image::setImage(const string &s){
    imageName = s;
}

Image::Image(Panel * pa,vec2 p,vec2 s,bool vis):Panel(pa,p,s,vis),dt(0){
    setImage("buttonglow.png");
}



