#include "structure.h"
#include "example.h"
#include <map>
#include <sstream>
#include "anim.h"
#include "game.h"
#include "button.h"
#include "resource.h"


void simpleCurrentCallback(Current* current, Chip* sourcechip, Chip*targetchip, Wire* wire){
    if (targetchip->getOwner() == current->getOwner()) {
        targetchip->chargeCount += current->getCharges();
    }
    else if (targetchip->chargeCount > targetchip->getDamage(current->getCharges())){
        targetchip->chargeCount -= targetchip->getDamage(current->getCharges());
    }
    else {
        targetchip->changeOwner(current->getOwner());
        targetchip->chargeCount = targetchip->getDamage(current->getCharges())-targetchip->chargeCount;
    }
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
    if (dt) {
        ExampleRenderer::getInstance().setColor(r, g, b, 255);
    }
    else{
        ExampleRenderer::getInstance().setColor(r, g, b, 255);
    }
    
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
    if (generateRate) {
        s.str("");
        s << (int)generateRate;
        ExampleRenderer::getInstance().printf(s.str(), dimension.pos);
    }
    ExampleRenderer::getInstance().resetColor();
    if (dt) {
        
        ExampleRenderer::getInstance().setColor(255, 255, 255, 255);
        ExampleRenderer::getInstance().drawImage("button_glow.png", dimension.pos+vec2(dt*50,-8), 0,vec2(1,1),vec2(64,16));
        ExampleRenderer::getInstance().drawImage("button_glow.png", dimension.pos+vec2(dt*25+dimension.size.x/2,-8), 0,vec2(1,2),vec2(64,16));
        ExampleRenderer::getInstance().drawImage("button_glow.png", dimension.pos +vec2(dt*(-50)+dimension.size.x+16,dimension.size.y), 0,vec2(1,1),vec2(64,16));
    }
    Widget::render();
}

void Chip::changeOwner(Player * p){
    double nr,nb,ng;
    if (p) {
        nr = p->r;
        ng = p->g;
        nb = p->b;
    }
    else{
        nr = 0;
        nb = 0;
        ng = 0;
    }
    if (owner) {
        owner->loseChip(this);
    }
    p->acquireChip(this);
    Anim<Chip>::getInstance().animate(this, &Chip::setR, r, nr, 1);
    Anim<Chip>::getInstance().animate(this, &Chip::setG, g, ng, 1);
    Anim<Chip>::getInstance().animate(this, &Chip::setB, b, nb, 1);
    owner = p;
    for (map<Chip*, Wire*>::iterator i=wires.begin();i!=wires.end(); i++) {
        if (i->first->owner == owner) {
            i->second->changeOwner(owner);
            i->first->boostWire();
        }
        else{
            i->second->changeOwner(0);
        }
    }
}

void Chip::boostWire(){
    for (map<Chip*, Wire*>::iterator i=wires.begin();i!=wires.end(); i++) {
        if (i->first->owner == owner) {
            i->second->changeOwner(owner);
        }
        else{
            i->second->changeOwner(0);
        }
    }
}

Chip::Chip(Widget * pa,vec2 p,vec2 s,bool vis):Widget(pa,p,s,vis),chargeCount(1),
    owner(0),highlighted(0),currentUpgrade(0),fortification(0){
    pg = new ProgressBar((Widget*)this,p+vec2(5,dimension.size.y-30),vec2(dimension.size.x-10,32),true);
        generateRate = s.x*s.y/10000;
        upgrades.push_back(new GenerationUpgrade(this));
        upgrades.push_back(new FortificationUpgrade(this));
        setColor(0, 0, 0);
}

void Chip::setSize(vec2 s){
    Widget::setSize(s);
    pg->setPosition(dimension.pos+vec2(5,dimension.size.y-30));
    pg->setSize(vec2(dimension.size.x-10,32));
}

Chip::~Chip(){
    delete pg;
    for(vector<Upgrade*>::iterator i=upgrades.begin(); i!=upgrades.end(); i++){
        delete (*i);
    }
}

void Chip::update(double t){
    chargeCount += t*generateRate;
    if (Control::getInstance().getPointer(0)->active &&
        hovered(vec2(Control::getInstance().getPointer(0)->x,
                     Control::getInstance().getPointer(0)->y))){
        dt+= t;
        Chip* c = game->getSelectedChip();
        if (c) {
            if (c->wires.find(this)!=c->wires.end()) {
                c->wires[this]->dt += t*50;
                highlighted = c->wires[this];
            };
        }
    }
    else{
        dt = 0;
        if (highlighted) {
            highlighted->dt = 0;
            highlighted = 0;
        }
    }
    if (currentUpgrade) {
        pg->setProgress(currentUpgrade->getProgress());
        if(currentUpgrade->update(t)){
            currentUpgrade->applyUpgrade(currentUpgrade->getLevel()+1);
            currentUpgrade = 0;
        }
    }
    else{
        pg->setProgress(0);
    }
}

void Chip::sendCurrent(Chip *c,int count){
    if (count == -1) {
        count = (int)(this->chargeCount/2);
    }
    if (wires.find(c)!=wires.end()) {
        wires[c]->sendCurrent(100,count,this,c,&simpleCurrentCallback);
    }
}

void Chip::pointerPressed(vec2 p, s3ePointerButton key,int id){
    Widget::pointerPressed(p,key,id);
    game->popWheel(this);
}


void Chip::pointerReleased(vec2 p, s3ePointerButton key,int id){
    Widget::pointerReleased(p,key,id);
    Chip* c = game->getSelectedChip();
    if (c) {
        c->sendCurrent(this);
    }
    //game->releaseWheel();
}

void Chip::addWire(Wire *w, Chip *c){
    wires[c] = w;
    w->game = game;
}

void Chip::setCurrentUpgrade(Upgrade *u){
    currentUpgrade = u;
}

double Chip::getDamage(double v){
    return v*(1-fortification);
}

vector<AttSubitems> Chip::getAttSubitems(){
    vector<AttSubitems> v;
    v.push_back((struct AttSubitems){
        ExampleRenderer::getInstance().getImage("button_glow.png"),
        "Charges",
        toString((int)chargeCount),
        "",
        "",
        ATT_BASE,
        ATT_NEUTRUAL
    });
    v.push_back((struct AttSubitems){
        ExampleRenderer::getInstance().getImage("generation.png"),
        "Generation",
        toString((int)(generateRate*60)),
        "",
        "",
        ATT_BASE,
        ATT_NEUTRUAL
    });
    stringstream ss;
    ss.setf(ios::fixed, ios::floatfield);
    ss.precision(1);
    ss << 100*fortification << "%";
    v.push_back((struct AttSubitems){
        ExampleRenderer::getInstance().getImage("fortification.png"),
        "Fortification",
        ss.str(),
        "",
        "",
        ATT_BASE,
        ATT_NEUTRUAL
    });
    vector<AttSubitems> uv;
    if (currentUpgrade) {
        uv = currentUpgrade->getAttSubitems(currentUpgrade->getLevel()+1);
    }
    v.insert( v.end(), uv.begin(), uv.end() );
    return v;
}

struct upgradeC {
    Chip* c;
    Upgrade *u;
    upgradeC(Chip* chip,Upgrade *up):c(chip),u(up){}
};

void UpgradeCB(const Widget *w, const Event){
    Button * b = (Button*) w;
    struct upgradeC * c = (struct upgradeC*) b->userdata;
    if (c->u->upgradable(c->u->getLevel()+1)) {
        c->c->setCurrentUpgrade(c->u);
        c->u->applyCost(c->u->getLevel()+1);
    }
}

void HoveringCB(const Widget *w, const Event){
    Button * b = (Button*) w;
    struct upgradeC * c = (struct upgradeC*) b->userdata;
    c->c->game->updateAttPanel(c->u->getAttSubitems(c->u->getLevel()+1));
}

void UpdateCB(const Widget *w,const Event){
    Button * b = (Button*) w;
    struct upgradeC * c = (struct upgradeC*) b->userdata;
    b->setActive((!c->c->getCurrentUpgrade()) && c->u->upgradable(c->u->getLevel()+1));
}

vector<Widget*> Chip::getWheelWidgets(){
    vector<Widget*> l;
    for (vector<Upgrade*>::iterator i=upgrades.begin(); i!=upgrades.end(); i++) {
        Button* b = new Button(0,vec2(0,0),vec2(80,80));
        //b->setText("a test");
        l.push_back(b);
        b->userdata = (void*) new struct upgradeC(this,*i);
        b->registerEvent("click", &UpgradeCB);
        b->registerEvent("hovering", &HoveringCB);
        b->registerEvent("update", &UpdateCB);
        b->setImage((*i)->getIcon());
    }
    return l;
}

void Wire::setSegments(vector<vec2> seg){
    segments = seg;
    length = 0;
    for (unsigned int i=1; i<segments.size(); i++) {
        vec2 a,b;
        a = segments[i];
        b=segments[i-1];
        length += (b-a).Length();
    }
}

void Wire::update(double dt){
    
    for (unsigned int i=0; i<currents.size(); i++) {
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
    ExampleRenderer::getInstance().setColor(r, g, b, 0xff);
    for (unsigned int i=1; i<segments.size(); i++) {
        vec2 a,b;
        a = segments[i];
        b=segments[i-1];
        if (dt) {
            ExampleRenderer::getInstance().drawImageQ("gradientarrow.png",
                                                      quad(vec2(dt,0), vec2((b-a).Length()+2,16)),
                                                      segments[i],
                                                      a.angleWith(b),vec2(1,1),
                                                      vec2(0, 8.0) );
        }
        else{
            ExampleRenderer::getInstance().drawImageQ("gradient.png",
                                                      quad(vec2(0,0), vec2((b-a).Length()+2,16)),
                                                      segments[i],
                                                      a.angleWith(b),vec2(1,1),
                                                      vec2(0, 8.0) );
        }
        
//        ExampleRenderer::getInstance().drawImageQ("gradient.png",
//                                                  quad(vec2(0,0), vec2((b-a).Length()+2),16),
//                                                  segments[i],
//                                                  a.angleWith(b),vec2(((b-a).Length()+2)/32,1),
//                                                  vec2(0, 8.0) );
    }
    for (unsigned int i=0; i<currents.size(); i++) {
        currents[i]->render();
    }
    ExampleRenderer::getInstance().resetColor();
}

void Wire::sendCurrent(double speed, int charges, Chip *source, Chip *target, CurrentCallback cb){
    bool reverse = false;
    if (source == this->target) {
        reverse = true;
    }
    /*
    unsigned int charges = (source->chargeCount/2);*/
    source->chargeCount -= charges;
    
    Current* c = new Current(this,1,speed,reverse,cb,charges);
    c->changeOwner(source->getOwner());
    c->game = game;
    currents.push_back(c);
    
}


void Wire::changeOwner(Player * p){
    double nr,nb,ng;
    if (p) {
        nr = p->r;
        ng = p->g;
        nb = p->b;
    }
    else{
        nr = 0;
        nb = 0;
        ng = 0;
    }
    Anim<Wire>::getInstance().animate(this, &Wire::setR, r, nr, 1);
    Anim<Wire>::getInstance().animate(this, &Wire::setG, g, ng, 1);
    Anim<Wire>::getInstance().animate(this, &Wire::setB, b, nb, 1);
    owner = p;
}

Wire::~Wire(){
    for (unsigned int i=0; i<currents.size(); i++) {
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
    pos = b + (double)(distanceOnSeg/l)*(a-b);
    p->setPosition(pos);
    p->update(dt);
    if (l<distanceOnSeg) {
        distanceOnSeg -= l;
        currentSeg ++;
    }
}

void Current::render(){
    ExampleRenderer::getInstance().setColor(r, g, b, 255);
    p->setSizes(vec2(MAX(MIN(2,charges/40.0),.5),0));
    p->render();
    ExampleRenderer::getInstance().resetColor();
}

void Current::changeOwner(Player * p){
    double nr,nb,ng;
    if (p) {
        nr = p->r;
        ng = p->g;
        nb = p->b;
    }
    else{
        nr = 0;
        nb = 0;
        ng = 0;
    }
    Anim<Current>::getInstance().animate(this, &Current::setR, r, nr, 1);
    Anim<Current>::getInstance().animate(this, &Current::setG, g, ng, 1);
    Anim<Current>::getInstance().animate(this, &Current::setB, b, nb, 1);
    owner = p;
}