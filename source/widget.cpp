#include "widget.h"
Control &c = Control::getInstance();
void Widget::pointerPressed(vec2 p, s3ePointerButton key,int id){
    for(widgetlist::iterator i = parent->children.begin(); i < parent->children.end(); i++){
        if((*i)->hovered(p)){
            (*i)->pointerPressed(p,key,id);
        } else {
            //do stuffs
        }
    }
}
void Widget::pointerReleased(vec2 p, s3ePointerButton key,int id){
    for(widgetlist::iterator i = parent->children.begin(); i < parent->children.end(); i++){
        if((*i)->hovered(p)){
            (*i)->pointerReleased(p,key,id);
        } else {
            //do stuffs
        }
    }
}
void Widget::registerEvent(std::string event,WidgetCallback cb){
    cblist[event] = cb;
}
void Widget::update(double dt){
    for (widgetlist::iterator i = children.begin(); i<children.end(); i++) {
        (*i)->update(dt);
    }
}
void Widget::render(){
    if (!visibility) return;
    for (widgetlist::iterator i = children.begin(); i<children.end(); i++) {
        (*i)->render();
    }

}
vec2 Widget::getPosition(){return dimension.pos;}
void Widget::setPosition(vec2 p){
    for (widgetlist::iterator i = children.begin(); i<children.end(); i++) {
        vec2 relativePos = (*i)->getPosition()-dimension.pos;
        (*i)->setPosition(relativePos+p);
    }
    dimension.pos = p;
}
void Widget::setX(double x){
    setPosition(vec2(x,dimension.pos.y));
}
void Widget::setY(double y){
    setPosition(vec2(dimension.pos.x,y));
}
vec2 Widget::getSize(){return dimension.size;}
void Widget::setSize(vec2 s){dimension.size = s;}
void Widget::setVisible(bool vis){
    vis = visibility;
}
void Widget::addChild(Widget * child){
    children.push_back(child);
}
void Widget::removeFromParent(){
    for (widgetlist::iterator i = parent->children.begin(); i<parent->children.end(); i++) {
        if (*i == this)
            parent->children.erase(i);
    }
    
}
void Widget::clearChildren(){
    for (widgetlist::iterator i = children.begin(); i<children.end(); i++) {
        (*i)->removeFromParent();
    }
}
bool Widget::hovered(vec2 p){
    return dimension.contain(p);
}