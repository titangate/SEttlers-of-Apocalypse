#include "label.h"
#include "example.h"


void Label::update(double dt){
    
}
void Label::render(){
    double x = 0;
    ExampleRenderer::getInstance().setColor(r, g, b, a);
    if(image){
        ExampleRenderer::getInstance().drawImage(image, dimension.pos, 0,imagesize/vec2(image->GetWidth(),image->GetHeight()));
        x = imagesize.x;
    }
    ExampleRenderer::getInstance().setFont(font);
    ExampleRenderer::getInstance().printf(text, dimension.pos+vec2(x,0),IW_2D_FONT_ALIGN_LEFT,IW_2D_FONT_ALIGN_CENTRE,dimension.size-vec2(x,0));
    ExampleRenderer::getInstance().resetColor();
}

void Label::setImage(CIw2DImage* img){
    image = img;
    imagesize = vec2(image->GetWidth(),image->GetHeight());
    setSize(rawsize);
}
void Label::setText(const string& s){
    text = s;
    setSize(rawsize);
}

void Label::setSize(vec2 s){
    rawsize = s;
    if (image) {
        dimension.size.y = MAX(MAX(s.y,imagesize.y),font->GetHeight());
        dimension.size.x = imagesize.x + s.x;
    }
    else{
        dimension.size.y = MAX(s.y,font->GetHeight());
        dimension.size.x = s.x;
    }
}


void Label::setImageSize(vec2 s){
    imagesize = s;
    setSize(rawsize);
}

Label::Label(Widget * pa,vec2 p,vec2 s,bool vis):Widget(pa,p,s,vis),
image(0),text(""),imagesize(0,0),rawsize(s){
    setFont(ExampleRenderer::getInstance().getCurrentFont());
}