#include "button.h"

void Button::render(){
    
}

void Button::pointerReleased(vec2 p, s3ePointerButton key,int id){
    if (cblist["click"]!=0) {
        Event e;
        
        (*cblist["click"])(this,e);
    }
}