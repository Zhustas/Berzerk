#include "../include/Body.h"

void Body::setPosition(V2 pos){
    position = pos;
}

V2 Body::getPosition() const {
    return position;
}

bool Body::touchedPlayer(V2 player) const {
    if ((position.x < player.x + 25 && player.x + 25 < position.x + 50) && (position.y < player.y + 25 && player.y + 25 < position.y + 50)){
        return true;
    }
    return false;
}

bool Body::shoot(V2 player) const {
    if (position.y < player.y + 25 && player.y + 25 < position.y + 50){
        return true;
    }
    if (position.x < player.x + 25 && player.x + 25 < position.x + 50) {
        return true;
    }
    return false;
}
