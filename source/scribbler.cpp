#include "scribbler.h"
#include "example.h"

void AttPanel::initDemo(){
    Label * l = new Label(this,dimension.pos,vec2(200,0));
    l->setImage(ExampleRenderer::getInstance().getImage("chip.png"));
    //l->setFont(ExampleRenderer::getInstance().getFont("24"));
    l->setText("AVERAGE");
    l->setImageSize(vec2(32,32));
}


extern quad getQuad(const string& name);
void AttPanel::render(){
    ExampleRenderer::getInstance().setColor(0, 0, 0, 100);
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("topleft"), vec2(dimension.pos.x-10,dimension.pos.y-10),0);
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("topright"), vec2(dimension.pos.x+dimension.size.x,dimension.pos.y-10),0);
    
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("botleft"), vec2(dimension.pos.x-10,dimension.pos.y+dimension.size.y),0);
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("botright"), vec2(dimension.pos.x+dimension.size.x,dimension.pos.y+dimension.size.y),0);
    
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("left"), vec2(dimension.pos.x-10,dimension.pos.y),0,vec2(1,dimension.size.y/10));
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("right"), vec2(dimension.pos.x+dimension.size.x,dimension.pos.y),0,vec2(1,dimension.size.y/10));
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("top"), vec2(dimension.pos.x,dimension.pos.y-10),0,vec2(dimension.size.x/10,1));
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("bot"), vec2(dimension.pos.x,dimension.pos.y+dimension.size.y),0,vec2(dimension.size.x/10,1));
    
    ExampleRenderer::getInstance().drawImageQ("standardbg.png", getQuad("mid"), vec2(dimension.pos.x,dimension.pos.y),0,vec2(dimension.size.x/10,dimension.size.y/10));
    ExampleRenderer::getInstance().resetColor();
    Widget::render();
}