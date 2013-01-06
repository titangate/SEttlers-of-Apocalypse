#include "menu.h"
#include "anim.h"


void NewGameCB(const Widget *w, const Event){
    Button * b = (Button*) w;
    Menu * m = (Menu*) b->userdata;
    m->dismiss();
}


Menu::Menu(Widget * w){
    base = w;
    
    
    g = new Game();
    g->standardGame(w);
    
    screenshield = new Label(base,vec2(0,0),base->getSize());
    screenshield->setImage(ExampleRenderer::getInstance().getImage("gradient.png"));
    screenshield->setImageSize(base->getSize());
    screenshield->setColor(0, 0, 0,0);
    Anim<Widget>::getInstance().animate((Widget*)screenshield, &Widget::setOpacity, 0, 255, 5);
    
    Button * b = new Button(w,vec2(w->getSize().x-300,w->getSize().y/2),vec2(200,48),true,false);
    b->userdata = this;
    Label * l = new Label(b,vec2(w->getSize().x-300,w->getSize().y/2),vec2(150,48));
    b->registerEvent("click", &NewGameCB);
    buttons.push_back(buttonitem(l,b));
    
    l->setImage(ExampleRenderer::getInstance().getImage("chip.png"));
    l->setFont(ExampleRenderer::getInstance().getFont("24"));
    l->setImageSize(vec2(40,40));
    l->setText("NEW GAME");
    
   
}

Menu::~Menu(){
    delete g;
}

void Menu::dismiss(){
    buttons[0].label->removeFromParent();
    buttons[0].button->removeFromParent();
    screenshield->removeFromParent();
    
}