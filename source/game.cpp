#include "game.h"
#include <math.h>
#include <list>
#include <queue>


typedef std::vector<Chip*> cp;
typedef std::vector<Wire*> wp;
void Game::update(double dt){
    //vec2 p = vec2(Control::getInstance().getPointer(0)->x,Control::getInstance().getPointer(0)->y);
    for (wp::iterator i=w.begin(); i!=w.end(); i++) {
        (*i)->update(dt);
    }/*
    for (cp::iterator i=c.begin(); i!=c.end(); i++) {
        (*i)->update(dt);
    }*/
}

void Game::render(){
    // Set up camera
    for (wp::iterator i=w.begin(); i!=w.end(); i++) {
        (*i)->render();
    }/*
    for (cp::iterator i=c.begin(); i!=c.end(); i++) {
        (*i)->render();
    }*/
    // Revert Camera
}

class CompareItem {
    
    
public:
    bool operator()(vec2& v1,vec2& v2){
        return v1.x<v2.x;
    }
};

int herustic_astar(vec2 start,vec2 finish){
    return fabs(start.y-finish.y)+fabs(start.x-finish.x);
}

struct neinode{
    vec2 item,
    double distance,
};

void astar(vec2 start,vec2 finish,int ** map){
    priority_queue<vec2, vector<vec2>, CompareItem> openset;
    static vec2 neighbour[] = {
        vec2(-1,-1),
        vec2(-1,0),
        vec2(-1,1),
        vec2(0,-1),
        vec2(0,1),
        vec2(1,-1),
        vec2(1,0),
        vec2(1,1),
    };
    openset.push(start);
    while (openset.size()) {
        vec2 current = openset.top();
        
        openset.pop();
    }
}

void Game::constructCircuits(){
    list<Wire*> w_res;
    for (int i=0; i<w.size(); i++) {
        w_res.push_back(w[i]);
    }
    //vector<Chip*> c_res = c;
    while (w_res.size()>0) {
        int i = rand()%w_res.size();
        list<Wire*>::iterator it = w_res.begin();
        for (int x=0; x<i; x++) {
            it++;
        }
        Wire * wire = *it;
        w_res.erase(it);
        Chip *c1 = wire->source, *c2 = wire->target;
    }
}

void Game::initDemo(Widget * base){
    
    vector<vec2> s;
    s.push_back(vec2(30,30));
    s.push_back(vec2(30,180));
    s.push_back(vec2(50,200));
    s.push_back(vec2(200,200));
    
    Chip* c1 = new Chip(base,vec2(100,100),vec2(150,150));
    Chip* c2 = new Chip(base,vec2(300,200),vec2(150,150));
    
    w.push_back(new Wire(s,c1,c2));
    c.push_back(c1);
    c.push_back(c2);
    c1->addWire(w[0],c2);
    c1->sendCurrent(c2);
}