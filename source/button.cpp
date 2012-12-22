#include "button.h"
#include "example.h"
#include <math.h>
#include "Iw2D.h"

void Button::render(){
    
    if (dt){
    ExampleRenderer::getInstance().drawImage("button_glow.png", dimension.pos+vec2(dt*50-64,-16), 0);
    ExampleRenderer::getInstance().drawImage("button_glow.png", dimension.pos +vec2(dt*(-50)+dimension.size.x-64,dimension.size.y-16), 0);
    }
    ExampleRenderer::getInstance().drawImage("button.png", dimension.pos, 0,dimension.size/50);
    ExampleRenderer::getInstance().printf(text.c_str(), dimension.pos,IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE,dimension.size);
    
}

void Button::update(double t){
    if (Control::getInstance().getPointer(0)->active &&
        hovered(vec2(Control::getInstance().getPointer(0)->x,
        Control::getInstance().getPointer(0)->y)))
        dt+= t;
    else
        dt = 0;
}

Button::Button(Widget * pa,vec2 p,vec2 s,bool vis):Widget(pa,p,s,vis),dt(0){
    setText("ha");
}
void Button::pointerReleased(vec2 p, s3ePointerButton key,int id){
    if (cblist["click"]!=0) {
        Event e;
        
        (*cblist["click"])(this,e);
    }
}