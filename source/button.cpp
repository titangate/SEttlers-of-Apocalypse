#include "button.h"
#include "example.h"
#include <math.h>
#include "Iw2D.h"

void Button::render(){
    
    if (dt){
    ExampleRenderer::getInstance().drawImage("button_glow.png", dimension.pos+vec2(dt*50-64,0), 0);
    ExampleRenderer::getInstance().drawImage("button_glow.png", dimension.pos +vec2(dt*(-50)+dimension.size.x-64,dimension.size.y-32), 0);
    }
    ExampleRenderer::getInstance().setColor(0, 255, 0, 255);
    ExampleRenderer::getInstance().drawImage("buttonbg.png", dimension.pos, 0,dimension.size/vec2(128,128));
    ExampleRenderer::getInstance().resetColor();
    if (image) {
        ExampleRenderer::getInstance().drawImage(image, dimension.pos, 0,dimension.size/vec2(image->GetWidth(),image->GetHeight()));
    }
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

void Button::setSize(vec2 s){
    s.y = s.x;
    Widget::setSize(s);
}

Button::~Button(){
    if (userdata) {
        delete userdata;
    }
}

Button::Button(Widget * pa,vec2 p,vec2 s,bool vis):Widget(pa,p,s,vis),dt(0),userdata(0),image(0){
    setText("ha");
    setSize(s);
}



void Button::pointerReleased(vec2 p, s3ePointerButton key,int id){
    if (cblist.find("click")!=cblist.end()) {
        Event e;
        
        (*cblist["click"])(this,e);
    }
}