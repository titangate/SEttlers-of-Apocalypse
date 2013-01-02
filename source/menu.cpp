#include "menu.h"
#include "anim.h"
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
    Label * l = new Label(b,vec2(w->getSize().x-300,w->getSize().y/2),vec2(150,48));
    
    l->setImage(ExampleRenderer::getInstance().getImage("chip.png"));
    l->setFont(ExampleRenderer::getInstance().getFont("24"));
    l->setImageSize(vec2(40,40));
    l->setText("NEW GAME");
    
   
}

Menu::~Menu(){
    delete g;
}