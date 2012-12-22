#include "panel.h"
#include "anim.h"
#include "example.h"
#include "button.h"
#include <math.h>
#include "Iw2D.h"
void Panel::update(double t){
    Widget::update(t);
}
void Panel::render(){
    ExampleRenderer::getInstance().drawImage("wheel.png", dimension.pos+vec2(128,128)/*+vec2(128,128)-vec2(dt,dt)*128*/,0, vec2(dt,dt),vec2(128,128));
    //percentsize = 0.0;
    if (fabs(dt-1)<.05){
        Widget::render();
    }
}

void Panel::generateButton(const std::string& s){
    Button* b = new Button(this,vec2(0,0),vec2(50,50));
    b->setText(s);
    addChild(b);
    for (int i=0; i<children.size(); i++) {
        double angle = i*M_PI*2/children.size();
        children[i]->setPosition(vec2(cos(angle),sin(angle))*90-vec2(25,10)+dimension.pos+dimension.size/2);
    }
    //ExampleRenderer::getInstance().translate(vec2(100,100));
    Anim<Panel>::getInstance().animate(this, &Panel::setPercent, 0, 1, 5);
}

void Panel::setPercent(double p){
    dt = p;
    
}


Panel::Panel(Widget * pa,vec2 p,vec2 s,bool vis):Widget(pa,p,s,vis){
    dt = 0;
    state = 1;
    
}