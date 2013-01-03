#include "game.h"
#include <math.h>
#include <algorithm>
#include <list>
#include <queue>
#include "panel.h"
#include "scribbler.h"
#include "anim.h"
#include "button.h"

typedef std::vector<Chip*> cp;
typedef std::vector<Wire*> wp;
void Game::update(double dt){
    for (wp::iterator i=w.begin(); i!=w.end(); i++) {
        (*i)->update(dt);
    }
    if (highlight) {
        const vector<AttSubitems> &v = highlight->getAttSubitems();
        for (unsigned int i=0; i<v.size(); i++) {
            ap->addItem(v[i]);
        }
    }
    ap->constructItems();
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


typedef vec2_t<int> vec2i;
int herustic_astar(vec2i start,vec2i finish){
    //return 0;
    return (abs(start.y-finish.y)+abs(start.x-finish.x))*10;
}

struct neinode{
    vec2i item;
    int distance;
};

class CompareItem {
    
    
public:
    bool operator()(neinode& v1,neinode& v2){
        return v1.distance > v2.distance;
    }
};

Widget* getObs(vector<vector<Widget*> > g,vec2i coord){
    return g[coord.x][coord.y];
}


vector<vec2i> constructPath(map<vec2i, vec2i> &comefrom,vector<vector<Widget*> > g,vec2i finish,Widget* source){
    vector<vec2i> r;
    vec2i current = finish;
    double angle = 10;
    //const vec2i horz(1,0);
    
    
    while (comefrom.find(current)!=comefrom.end()) {
        if (comefrom[current].angleWith(current)!=angle) {
            
            r.push_back(current);
            angle = comefrom[current].angleWith(current);
            //printf("%g\n",angle);
        }
        //r.push_back(comefrom[current]);
        current = comefrom[current];
        if (getObs(g, current)==source) {
            comefrom.erase(current);
        }
    }
    r.push_back(current);
    reverse(r.begin(),r.end());
    //r.push_back(comefrom[current]);
    return r;
}


const int division = 10;


vector<vec2i> astar(vec2i start,vec2i finish,vector<vector<Widget*> > g,Widget* startWidget,Widget* finishWidget,Widget* boundaryWidget){
    priority_queue<neinode, vector<neinode>, CompareItem> openset;
    static neinode neighbour[] = {
        {vec2i(-1,-1),14},
        {vec2i(-1,0),10},
        {vec2i(-1,1),14},
        {vec2i(0,-1),10},
        {vec2i(0,1),10},
        {vec2i(1,-1),14},
        {vec2i(1,0),10},
        {vec2i(1,1),14}
    }; // all adjcent node
    map<vec2i, vec2i> comefrom;
    map<vec2i, int> visited;
    map<vec2i, bool> closedset;
    neinode nei = {start,herustic_astar(start, finish)};// starting node
    openset.push(nei);
    visited[start] = 0;
    while (openset.size()) { // terminates if the openset is empty
        neinode newitem = openset.top();
        vec2i current = newitem.item;
        
        openset.pop();
        if (closedset.find(newitem.item)!=closedset.end()) {
            continue;
        }
        closedset[newitem.item] = true;
        //printf("%d %d testing with %d\n",current.x,current.y,newitem.distance);
        for (int i=0; i<8; i++) {
            neinode n = neighbour[i];
            vec2i tester = current + n.item;
            int newdistance = n.distance + visited[current];
            Widget* w = getObs(g, tester);
            if (w==finishWidget) {
               
                    //comefrom[tester] = current;
                    return constructPath(comefrom,g, current,startWidget);
                
            }else if (visited.find(tester)==visited.end() || visited[tester] > newdistance) {
                if (getObs(g, tester) == boundaryWidget) {
                    continue;
                }
                else{
                    visited[tester] = newdistance;
                    comefrom[tester] = current;
                    nei.item = tester;
                    //printf("%d %d: %d\n",tester.x,tester.y, herustic_astar(tester, finish)+newdistance);
                    nei.distance = newdistance + herustic_astar(tester, finish);
                    openset.push(nei);
                    //printf("%d %d testing with %d is now on top\n",openset.top().item.x,openset.top().item.y,openset.top().distance);
                }
            }
        }
    }
    return vector<vec2i>();
}

// map floating coordinate to discrete integer ones
vec2i coord(vec2 v){
    return vec2i(v.x/division,v.y/division);
}



vector<vector<Widget*> > constructGraph(vector<Chip*> chips, vec2i size,Widget* boundaryWidget){
    vector<vector<Widget*> > g;
    // initialize the graph
    for (int i=0; i<size.x; i++) {
        g.push_back(vector<Widget*>());
        for (int j=0; j<size.y; j++) {
            g[i].push_back((Widget*)0);
        }
    }
    // top and bottom boundary
    for (int i=0; i<size.x; i++) {
        g[i][0] = boundaryWidget;
        g[i][size.y-1] = boundaryWidget;
    }
    // left and right boundary
    for (int i=0; i<size.y; i++) {
        g[0][i] = boundaryWidget;
        g[size.x-1][i] = boundaryWidget;
    }
    // iterate through chips to map coordinations
    for (vector<Chip*>::iterator i=chips.begin(); i!=chips.end(); i++) {
        Chip* c = *i;
        vec2i topleft = coord(c->getPosition()),botright = coord(c->getPosition()+c->getSize());
        for (int x=topleft.x; x<botright.x;x++) {
            for (int y = topleft.y; y<botright.y; y++) {
                g[x][y] = c;
            }
        }
    }
    return g;
}

void Game::constructCircuits(){
    list<Wire*> w_res;
    for (unsigned int i=0; i<w.size(); i++) {
        w_res.push_back(w[i]);
    }
    vector<vector<Widget*> > g = constructGraph(c,vec2i(100,100),(Widget*)1);
    while (w_res.size()>0) {
        int i = rand()%w_res.size();
        list<Wire*>::iterator it = w_res.begin();
        for (int x=0; x<i; x++) {
            it++;
        }
        Wire * wire = *it;
        w_res.erase(it);
        Chip *c1 = wire->source, *c2 = wire->target;
        vector<vec2i> path = astar(coord(c1->getCentre()), coord(c2->getCentre()), g, c1, c2, (Widget*)1);
        vector<vec2> seg;
        g[path[0].x][path[0].y] = (Widget*)1;
        g[path[path.size()-1].x][path[path.size()-1].y] = (Widget*)1;
        for (unsigned int i=0; i<path.size(); i++) {
            seg.push_back(vec2((path[i].x+.5)*division,(path[i].y+.5)*division));
        }
        wire->setSegments(seg);
    }
}
void Game::popWheel(Chip * w){
    const vec2 s(50,50);
    p->setVisible(true);
    p->clearWheel();
    vector<Widget*> buttons = w->getWheelWidgets();
    p->pop();
    double b = MIN(w->getSize().x,w->getSize().y);
    p->setSize(vec2(b,b)+s);
    p->setPosition(w->getPosition()-s/2.0);
    
    for (vector<Widget*>::iterator i=buttons.begin(); i!=buttons.end(); i++) {
        p->addWheelWidget(*i);
    }
    highlight = w;
}

void Game::releaseWheel(){
    p->release();   
    highlight = NULL;
}


Chip* Game::getSelectedChip(){
    return highlight;
}

void commenceVictory(const Widget * w,Event e){
    Game *g = (Game*) ((Button*)w)->userdata;
    g->victory();
}

void Game::initDemo(Widget * ba){
    
    /*vector<vec2> s;
    s.push_back(vec2(30,30));
    s.push_back(vec2(30,180));
    s.push_back(vec2(50,200));
    s.push_back(vec2(200,200));
    
    Chip* c1 = new Chip(base,vec2(100,100),vec2(300,150));
    Chip* c2 = new Chip(base,vec2(800,200),vec2(150,150));
    Player *n = new Player();
    
    c1->changeOwner(n);
    c1->game = this;
    c2->game = this;
    w.push_back(new Wire(s,c1,c2));
    w.push_back(new Wire(s,c2,c1));
    c.push_back(c1);
    c.push_back(c2);
    c1->addWire(w[0],c2);
    c2->addWire(w[1],c1);
    constructCircuits();
    c1->sendCurrent(c2);*/
    
    // selection wheel
    
    base = ba;
    randomTerrain(base->getSize(), 10);
    
    p = new Panel(base,vec2(50,50),vec2(256,256));
    p->setVisible(false);
    
    ap = new AttPanel(base,vec2(10,base->getSize().y-150),vec2(base->getSize().x/2,130));
    ap->initDemo();
    
    Button * b = new Button(base,vec2(base->getSize().x/2,base->getSize().y-70),vec2(64,64));
    b->setText("Victory");
    b->registerEvent("click", &commenceVictory);
    b->userdata = (void*) this;
}

void Game::standardGame(Widget * ba){
    base = ba;
    randomTerrain(base->getSize(), 10);
    
    p = new Panel(base,vec2(50,50),vec2(256,256));
    p->setVisible(false);
    //a
    ap = new AttPanel(base,vec2(10,base->getSize().y-150),vec2(base->getSize().x/2,130));
    player = new Player();
    Player * enemy = new Player();
    enemy->r = enemy->g = enemy->b = 0;
    
    c[0]->changeOwner(player);
    for (unsigned int i=1; i<c.size(); i++) {
        c[i]->changeOwner(enemy);
    }
    player->setDelegate(this);
    enemy->setDelegate(this);
    players.insert(player);
    players.insert(enemy);
    //ap->initDemo();

}

void Game::eliminate(Player* p){
    players.erase(p);
    if (p == player) {
        fail();
    }

    else if (players.size()==1) {
        victory();
    }
}

bool Game::_overlapWithExisted(vec2 pos,vec2 size){
    for (vector<Chip *>::iterator i = c.begin(); i!=c.end(); i++) {
        if ((*i)->dimension.overlap(quad(pos,size))) {
            return true;
        }
    }
    return false;
}

void Game::randomTerrain(vec2 s,unsigned int chipcount){
    vec2 pos,size;
    while (chipcount--) {
        do {
            size.x = rand()%100+80;
            size.y = rand()%100+80;
            pos.x = rand()%(int)(s.x-size.x);
            pos.y = rand()%(int)(s.y-size.y);
        } while (_overlapWithExisted(pos, size));
        c.push_back(new Chip(base,pos,size));
    }
    for (vector<Chip*>::iterator i=c.begin(); i!=c.end(); i++) {
        (*i)->setSize((*i)->getSize()-vec2(30,30));
        (*i)->game = this;
        for (vector<Chip*>::iterator j=c.begin(); j!=c.end(); j++) {
            if ((*i)!=(*j)) {
                Wire * wire = new Wire(vector<vec2>(),(*i),(*j));
                w.push_back(wire);
                (*i)->addWire(wire, *j);
            }
        }
        
    }
    constructCircuits();
}

void Game::updateAttPanel(vector<AttSubitems> v){
    for (unsigned int i=0; i<v.size(); i++) {
        ap->addItem(v[i]);
    }
}

void Game::clear(){
    for (unsigned int i=0; i<c.size(); i++) {
        c[i]->removeFromParent();
        delete c[i];
    }
    c.clear();
    for (unsigned int i=0; i<w.size(); i++) {
        delete w[i];
    }
    w.clear();
    for (set<Player *>::iterator i = players.begin();i!=players.end();) {
        delete (*i);
    }
    players.clear();
    player = 0;
}

void Game::fail(){
    releaseWheel();
    ap->setVisible(false);
    Label * screenshield = new Label(base,vec2(0,0),base->getSize());
    screenshield->setImage(ExampleRenderer::getInstance().getImage("gradient.png"));
    screenshield->setImageSize(base->getSize());
    screenshield->setColor(0, 0, 0,0);
    Anim<Widget>::getInstance().animate((Widget*)screenshield, &Label::setOpacity, 0, 255, 5);
    
    
    Label * bigtext = new Label(base,vec2(50,0),base->getSize()-vec2(50,0));
    bigtext->setText("YOU HAVE BEEN ELIMINATED");
    bigtext->setFont(ExampleRenderer::getInstance().getFont("48"));
    Anim<Widget>::getInstance().animate((Widget*)bigtext, &Label::setOpacity, 0, 255, 5);
    Anim<Widget>::getInstance().animate((Widget*)bigtext, &Label::setG, 255, 0, 5);
    Anim<Widget>::getInstance().animate((Widget*)bigtext, &Label::setB, 255, 0, 5);
    
    Button * backButton = new Button(base,vec2(base->getSize().x-100,base->getSize().y/2+30),vec2(64,64));
    backButton->setImage(ExampleRenderer::getInstance().getImage("tick.png"));
    Anim<Widget>::getInstance().animate((Widget*)backButton, &Widget::setOpacity, 0, 255, 5);
}

void Game::victory(){
    releaseWheel();
    ap->setVisible(false);
    Label * screenshield = new Label(base,vec2(0,0),base->getSize());
    screenshield->setImage(ExampleRenderer::getInstance().getImage("gradient.png"));
    screenshield->setImageSize(base->getSize());
    screenshield->setColor(0, 0, 0,0);
    Anim<Widget>::getInstance().animate((Widget*)screenshield, &Label::setOpacity, 0, 255, 5);
    
    
    Label * bigtext = new Label(base,vec2(50,0),base->getSize()-vec2(50,0));
    bigtext->setText("YOU HAVE LED YOUR BITS TO VICTORY");
    bigtext->setFont(ExampleRenderer::getInstance().getFont("48"));
    Anim<Widget>::getInstance().animate((Widget*)bigtext, &Label::setOpacity, 0, 255, 5);
    
    Button * backButton = new Button(base,vec2(base->getSize().x-100,base->getSize().y/2+30),vec2(64,64));
    backButton->setImage(ExampleRenderer::getInstance().getImage("tick.png"));
    Anim<Widget>::getInstance().animate((Widget*)backButton, &Widget::setOpacity, 0, 255, 5);
}