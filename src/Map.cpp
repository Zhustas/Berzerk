#include "../include/Map.h"

Map::Map(const std::string &file_name, char came_from) : width(CONSTANTS::MAP_WIDTH), height(CONSTANTS::MAP_HEIGHT), block_size(CONSTANTS::BLOCK_SIZE), came_from(came_from) {
    load(file_name);
}

Map::~Map() = default;

void Map::draw(){
    int offset_x = 0, offset_y = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (map[i][j] == WALL){
                DrawRectangle(offset_x, offset_y, block_size, block_size, BLUE);
            }
            offset_x += block_size;
        }
        offset_x = 0;
        offset_y += block_size;
    }
}

void Map::load(const std::string& file_name){
    if (!map.empty()){
        map.clear();
    }

    std::ifstream file(file_name);

    if (file.is_open()){
        std::string line;
        while (std::getline(file, line)){
            map.push_back(line);
        }

        file.close();
        buildWalls();
    } else {
        std::cout << "Error: failed to open " << file_name << std::endl;
    }
}

void Map::buildWalls(){
    if (came_from == 'L'){
        map[7][0] = WALL;
        map[8][0] = WALL;
        map[9][0] = WALL;
    } else if (came_from == 'D'){
        map[height - 1][11] = WALL;
        map[height - 1][12] = WALL;
        map[height - 1][13] = WALL;
    } else if (came_from == 'U'){
        map[0][11] = WALL;
        map[0][12] = WALL;
        map[0][13] = WALL;
    } else {
        map[7][width - 1] = WALL;
        map[8][width - 1] = WALL;
        map[9][width - 1] = WALL;
    }
}

Vector2 Map::getPlayerPosition() const {
    if (came_from == 'L'){
        return {100, 400};
    } else if (came_from == 'D'){
        return {600, 15 * 50};
    } else if (came_from == 'U'){
        return {600, 50};
    }
    return {1000, 400};
}

char Map::getWhereCameFrom() const {
    return came_from;
}

bool Map::isOutOfMapPlayer(Vector2 player_pos) {
    if (player_pos.x < 0){
        came_from = 'R';
        return true;
    } else if (player_pos.x > float(width * 50)){
        came_from = 'L';
        return true;
    } else if (player_pos.y < 0){
        came_from = 'D';
        return true;
    } else if (player_pos.y > float(height * 50)){
        came_from = 'U';
        return true;
    }
    return false;
}

std::vector<Vector2> Map::getEnemiesPositions(){
    std::vector<Vector2> positions;
    for (int i = 0; i < height; i++){
        if (map[i].contains('E')){
            for (int j = 0; j < width; j++){
                if (map[i][j] == 'E'){
                    positions.emplace_back(50 * j, 50 * i);
                }
            }
        }
    }
    return positions;
}

bool* Map::getMovingDirectionsForEnemy(Vector2 pos) const {
    int i = (int) pos.y / 50, j = (int) pos.x / 50;

    bool* dirs = new bool[4];
    dirs[0] = false;
    dirs[1] = false;
    dirs[2] = false;
    dirs[3] = false;
    if (map[i - 1][j] != WALL){
        dirs[0] = true;
    }
    if (map[i][j + 1] != WALL){
        dirs[1] = true;
    }
    if (map[i + 1][j] != WALL){
        dirs[2] = true;
    }
    if (map[i][j - 1] != WALL){
        dirs[3] = true;
    }

    return dirs;
}

bool Map::isWallBody(Vector2 position){
    if ((position.y + 5) / 50 >= (float) height || (position.x + 5) / 50 >= (float) width){
        return false;
    } else {
        if (map[int((position.y + 5) / 50)][int((position.x + 5) / 50)] == WALL){
            return true;
        }
    }
    position.x += 45;
    position.y += 5;
    if (position.y / 50 >= (float) height || position.x / 50 >= (float) width) {
        return false;
    } else {
        if (map[int(position.y / 50)][int(position.x / 50)] == WALL){
            return true;
        }
    }
    position.y += 40;
    if (position.y / 50 >= (float) height){
        return false;
    } else {
        if (map[int(position.y / 50)][int(position.x / 50)] == WALL){
            return true;
        }
    }
    position.x -= 45;
    if (map[int(position.y / 50)][int(position.x / 50)] == WALL){
        return true;
    }
    return false;
}

bool Map::isWallOrIsOutOfMapBullet(Vector2 position){
    int j = int(position.y / 50), i = int(position.x / 50);
    if (j < 0 || i < 0 || j >= height || i >= width){
        return true;
    }
    if (map[j][i] == WALL){
        return true;
    }
    return false;
}
