#include "panel.h"
#include "anim.h"
#include "example.h"
#include "button.h"
#include <math.h>
#include "Iw2D.h"
void Panel::update(double t){
    Widget::update(t);
    /*if (percentsize) {
        setVisible(true);
    }
    else setVisible(false);*/
}
void Panel::render(){
    if (!visibility) {
        return;
    }
    ExampleRenderer::getInstance().setColor(100, 100, 100, 0xff);
    ExampleRenderer::getInstance().drawImage("wheel.png", dimension.pos+dimension.size/2,0, vec2(dt,dt),vec2(128,128));
    ExampleRenderer::getInstance().resetColor();
    //percentsize = 0.0;
    if (fabs(dt-1)<.05){
        Widget::render();
    }
}

void Panel::addWheelWidget(Widget *b){
    addChild(b);
    for (unsigned int i=0; i<children.size(); i++) {
        double angle = i*M_PI*2/children.size();
        children[i]->setPosition(vec2(cos(angle),sin(angle))*(dimension.size.x/2-10)
                                 +dimension.pos+dimension.size/2
                                 -b->getSize()/2
                                 );
    }
}

void Panel::clearWheel(){
    for (unsigned int i=0; i<children.size(); i++) {
        delete children[i];
    }
    children.clear();
}

void Panel::generateButton(const std::string& s){
    Button* b = new Button(this,vec2(0,0),vec2(50,50));
    b->setText(s);
    addWheelWidget(b);
    //ExampleRenderer::getInstance().translate(vec2(100,100));
}

void Panel::pop(){
    
    Anim<Panel>::getInstance().animate(this, &Panel::setPercent, 0, 1, .3,"quadOut");
}

void Panel::release(){
    Anim<Panel>::getInstance().animate(this, &Panel::setPercent, 1, 0, .3,"quadOut");
}

void Panel::setPercent(double p){
    dt = p;
    
}


Panel::Panel(Widget * pa,vec2 p,vec2 s,bool vis):Widget(pa,p,s,vis){
    dt = 0;
    state = 1;
    
}