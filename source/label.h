#ifndef LABEL_H
#define LABEL_H
#include "widget.h"
#include "Iw2D.h"
class Label : public Widget{
    CIw2DImage* image;
    std::string text;
    vec2 imagesize;
    CIw2DFont * font;
    vec2 rawsize;
    //uint8 r,g,b,a;
public:
    
    void update(double dt) ;
    void render() ;
    void setSize(vec2);
    void setImage(CIw2DImage* img);
    void setText(const std::string& s);
    void setImageSize(vec2 s);
    void setFont(CIw2DFont *f){font = f;setSize(rawsize);}
    Label(Widget * pa,vec2 p,vec2 s,bool vis = true);
};

#endif