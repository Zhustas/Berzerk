#include "../include/Map.h"

Map::Map() : width(CONSTANTS::MAP_WIDTH), height(CONSTANTS::MAP_HEIGHT), block_size(CONSTANTS::BLOCK_SIZE) {}

bool Map::isOutOfMapPlayer(V2 player) const {
    if (player.x < 0){
        return true;
    } else if (player.x > float(width * block_size)){
        return true;
    } else if (player.y < 0){
        return true;
    } else if (player.y > float(height * block_size)){
        return true;
    }
    return false;
}
