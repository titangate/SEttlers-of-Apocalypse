#include "game.h"


typedef std::vector<Player*> vp;
void Game::update(double dt){
    for (vp::iterator i=player.begin(); i!=player.end(); i++) {
        (*i)->update(dt);
    }
}

void Game::render(){
    // Set up camera
    for (vp::iterator i=player.begin(); i!=player.end(); i++) {
        (*i)->render();
    }
    // Revert Camera
}