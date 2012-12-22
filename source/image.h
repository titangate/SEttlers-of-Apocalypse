#ifndef IMAGE_H
#define IMAGE_H
#include "panel.h"
using namespace std;
class Image: public Panel{
public:
    void render();
    void update (double dt);
    void setImage(const string & s);
    Image(Panel * pa,vec2 p,vec2 s,bool vis = true);
double dt;
    string imageName;
};

#endif