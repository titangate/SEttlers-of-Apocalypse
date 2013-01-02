#ifndef MENU_H
#define MENU_H
#include "label.h"
#include "button.h"
#include "game.h"
#include <vector>

class Menu {
    
    Game * g;
    Widget * base;
    Label * screenshield;
    std::vector<Button *> buttons;
    
public:
    void update(double dt){g->update(dt);}
    void render(){g->render();}
    Menu(Widget *w);
    ~Menu();
};

#endif