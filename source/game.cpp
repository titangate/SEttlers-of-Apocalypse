#include "game.h"
#include <math.h>
#include <algorithm>
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
            printf("%g\n",angle);
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
        printf("%d %d testing with %d\n",current.x,current.y,newitem.distance);
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
            seg.push_back(vec2((path[i].x)*division,(path[i].y)*division));
        }
        wire->setSegments(seg);
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
    w.push_back(new Wire(s,c2,c1));
    w.push_back(new Wire(s,c2,c1));
    c.push_back(c1);
    c.push_back(c2);
    c1->addWire(w[0],c2);
    c1->addWire(w[1],c2);
    c1->addWire(w[2],c2);
    constructCircuits();
    c1->sendCurrent(c2);
}