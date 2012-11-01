#ifndef UI_H
#define UI_H


#include <math.h>
#include <string>
#include "core.h"
class Widget;

class UI{
public:
    void update(double dt);
    void render();
    void create(std::string s,Widget* parent);
    UI();
protected:
};


#endif