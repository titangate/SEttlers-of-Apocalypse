#include "player.h"

//typedef std::vector<Resource*> vp;
//typedef std::vector<Structure*> rv;

void Player::acquireChip(Chip * c){
    chips.insert(c);
    if (del) {
        del->acquiredChip(this,c);
    }
}

void Player::loseChip(Chip * c){
    chips.erase(c);
    if (del) {
        del->loseChip(this,c);
    }
    if (eliminated()) {
        if (del) {
            del->elimate(this);
        }
    }
}