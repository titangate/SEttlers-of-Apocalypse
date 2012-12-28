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

void AttPanel::clear(){
    for (unsigned int i=0; i<children.size(); i++) {
        delete children[i];
    }
    children.clear();
    y = 0;
}

void AttPanel::constructItems(){
    clear();
    for (map<string, AttSubitems>::iterator i = atts.begin();i!=atts.end();i++) {
        const AttSubitems& att = i->second;
        Label * left = new Label(this,dimension.pos+vec2(0,y),vec2(secondDiv,0));
        left->setText(att.item);
        left->setImage(att.icon);
        left->setImageSize(vec2(32,32));
        Label * mid1 = new Label(this,dimension.pos+vec2(secondDiv,y),vec2(secondDiv/2,left->getSize().y));
        mid1->setText(att.current);
        Label * mid2 = new Label(this,dimension.pos+vec2(thirdDiv,y),vec2(secondDiv/2,left->getSize().y));
        mid2->setText(att.after);
        Label * right = new Label(this,dimension.pos+vec2(fourthDiv,y),vec2(secondDiv,left->getSize().y));
        right->setText(att.modifier);
        if (att.boost == ATT_POSITIVE) {
            right->setImage(ExampleRenderer::getInstance().getImage("uparrow.png"));
            right->setImageSize(vec2(32,32));
            right->setColor(0, 255, 0);
            mid2->setColor(0, 255, 0);
        }
        else if (att.boost == ATT_NEGATIVE){
            right->setImage(ExampleRenderer::getInstance().getImage("downarrow.png"));
            right->setImageSize(vec2(32,32));
            right->setColor(255, 0, 0);            
            mid2->setColor(255, 0, 0);
        }
        else if (att.boost == ATT_DISABLE){
            right->setColor(125, 125, 125);
            mid2->setColor(125, 125, 125);
        }
        y += left->getSize().y;
    }
    atts.clear();
}

void AttPanel::addItem(AttSubitems a){
    if (atts.find(a.item)!=atts.end()) {
        if (a.cat == ATT_BASE) {
            return;
        }
    }
    atts[a.item] = a;
}