#ifndef MENU_H
#define MENU_H
#include "label.h"
#include "button.h"
#include "game.h"
#include <vector>

class buttonitem {
public:
    Label * label;
    Button * button;
    buttonitem(Label * label,Button* button):label(label),button(button){}
    
};

class Menu {
    
    Game * g;
    Widget * base;
    Label * screenshield;
    std::vector<buttonitem> buttons;
    
    
public:
    void update(double dt){g->update(dt);}
    void render(){g->render();}
    void dismiss();
    Menu(Widget *w);
    ~Menu();
};

#endif