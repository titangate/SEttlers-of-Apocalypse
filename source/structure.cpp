#include "structure.h"
#include "example.h"
#include <map>
#include <sstream>

void simpleCurrentCallback(Current* current, Chip* sourcechip, Chip*targetchip, Wire* wire){
    targetchip->receiveCharge(10);
}

quad getQuad(const string& name){
    
    static map<string,quad> quads;
    if (quads.find(name)!=quads.end()) {
        return quads[name];
    }
    quads["topleft"] = quad(vec2(0, 0), vec2(10, 10));
    quads["topright"] = quad(vec2(40, 0), vec2(10, 10));
    quads["botleft"] = quad(vec2(0, 40), vec2(10, 10));
    quads["botright"] = quad(vec2(40, 40), vec2(10, 10));
    quads["top"] = quad(vec2(10, 0), vec2(10, 10));
    quads["bot"] = quad(vec2(10, 40), vec2(10, 10));
    quads["left"] = quad(vec2(0, 10), vec2(10, 10));
    quads["right"] = quad(vec2(40, 10), vec2(10, 10));
    quads["mid"] = quad(vec2(10, 10), vec2(10, 10));
    return quads[name];
}

void Chip::render(){
    ExampleRenderer::getInstance().setColor(48, 192, 23, 128);
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("topleft"), vec2(dimension.pos.x-10,dimension.pos.y-10),0);
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("topright"), vec2(dimension.pos.x+dimension.size.x,dimension.pos.y-10),0);
    
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("botleft"), vec2(dimension.pos.x-10,dimension.pos.y+dimension.size.y),0);
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("botright"), vec2(dimension.pos.x+dimension.size.x,dimension.pos.y+dimension.size.y),0);
    
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("left"), vec2(dimension.pos.x-10,dimension.pos.y),0,vec2(1,dimension.size.y/10));
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("right"), vec2(dimension.pos.x+dimension.size.x,dimension.pos.y),0,vec2(1,dimension.size.y/10));
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("top"), vec2(dimension.pos.x,dimension.pos.y-10),0,vec2(dimension.size.x/10,1));
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("bot"), vec2(dimension.pos.x,dimension.pos.y+dimension.size.y),0,vec2(dimension.size.x/10,1));
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("mid"), vec2(dimension.pos.x,dimension.pos.y),0,vec2(dimension.size.x/10,dimension.size.y/10));
    stringstream s;
    s << (int)chargeCount;
    ExampleRenderer::getInstance().setColor(255, 255, 255, 255);
    ExampleRenderer::getInstance().setFont("48");
    ExampleRenderer::getInstance().printf(s.str(), dimension.pos,IW_2D_FONT_ALIGN_CENTRE,IW_2D_FONT_ALIGN_CENTRE,dimension.size);
    ExampleRenderer::getInstance().setFont("arial14");
    ExampleRenderer::getInstance().resetColor();
    Widget::render();
}


Chip::Chip(Widget * pa,vec2 p,vec2 s,bool vis):Widget(pa,p,s,vis),chargeCount(1){
    pg = new ProgressBar((Widget*)this,p+vec2(10,dimension.size.y-50),vec2(dimension.size.x-20,32),true);
    generateRate = s.x*s.y/10000;
    //pg->setSize(vec2(dimension.size.x,32));
}

void Chip::update(double dt){
    chargeCount += dt*generateRate;
}

void Chip::sendCurrent(Chip *c){
    if (wires.find(c)!=wires.end()) {
        wires[c]->sendCurrent(100,this,c,&simpleCurrentCallback);
    }
}

void Wire::update(double dt){
    
    for (int i=0; i<currents.size(); i++) {
        currents[i]->update(dt);
    }
}

void Wire::killCurrent(Current *c){
    vector<Current *>::iterator i = find(currents.begin(),currents.end(),c);
    if (i!=currents.end()) {
        delete (*i);
        currents.erase(i);
    }
}


void Wire::render(){
    for (int i=1; i<segments.size(); i++) {
        vec2 a,b;
        a = segments[i];
        b=segments[i-1];
        ExampleRenderer::getInstance().drawImage("gradient.png",
                                                 segments[i],
                                                 a.angleWith(b),vec2(((b-a).Length()+2)/32,1),
                                                 vec2(0, 8.0) );
    }
    for (int i=0; i<currents.size(); i++) {
        currents[i]->render();
    }
}

void Wire::sendCurrent(double speed, Chip *source, Chip *target, CurrentCallback cb){
    bool reverse = false;
    if (source == this->target) {
        reverse = true;
    }
    Current* c = new Current(this,1,speed,reverse,cb);
    currents.push_back(c);
    
}

Wire::~Wire(){
    for (int i=0; i<currents.size(); i++) {
        delete currents[i];
    }
}


void Current::update(double dt){
    if (currentSeg==wire->segments.size()){
        if (cb) {
            if (reverse) {
                (*cb)(this,wire->target,wire->source,wire);
            }
            else{
                (*cb)(this,wire->source,wire->target,wire);
            }
            
        }
        wire->killCurrent(this);
        //p->update(dt);
        return;
    }
    distanceOnSeg += dt*currentSpeed;
    vec2 a,b;
    a = wire->segments[currentSeg];
    //if (currentSeg==0) b=wire->segments[wire->segments.size()-1];
    b=wire->segments[currentSeg-1];
    double l = (b-a).Length();
    pos = b + distanceOnSeg/l*(a-b);
    p->setPosition(pos);
    p->update(dt);
    if (l<distanceOnSeg) {
        distanceOnSeg -= l;
        currentSeg ++;
    }
}

void Current::render(){
    p->render();
}