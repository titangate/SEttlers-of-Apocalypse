#include "player.h"

typedef std::vector<Resource*> vp;
//typedef std::vector<Structure*> rv;
void Player::update(double dt){
    for (vp::iterator i=resource.begin(); i!=resource.end(); i++) {
        (*i)->update(dt);
    }
}

void Player::render(){
    // Set up camera
    for (vp::iterator i=resource.begin(); i!=resource.end(); i++) {
        (*i)->render();
    }
    // Revert Camera
}