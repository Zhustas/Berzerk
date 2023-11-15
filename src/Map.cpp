#include <fstream>
#include <iostream>
#include "raylib.h"
#include "../include/Map.h"
#include "../include/Utils.h"

Map::Map() = default;

Map::Map(const std::string &file_name, char came_from) {
    this->came_from = came_from;
    load(file_name);
}

Map::~Map() = default;

void Map::load(const std::string& file_name){
    if (!map.empty()){
        map.clear();
    }

    std::ifstream file(file_name);

    std::string line;
    while (std::getline(file, line)){
        map.push_back(line);
    }

    file.close();

    buildWalls();
}

void Map::buildWalls(){
    if (came_from == 'L'){
        map[7][0] = '#';
        map[8][0] = '#';
        map[9][0] = '#';
    } else if (came_from == 'D'){
        map[height - 1][11] = '#';
        map[height - 1][12] = '#';
        map[height - 1][13] = '#';
    } else if (came_from == 'U'){
        map[0][11] = '#';
        map[0][12] = '#';
        map[0][13] = '#';
    } else {
        map[7][width - 1] = '#';
        map[8][width - 1] = '#';
        map[9][width - 1] = '#';
    };
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

void Map::draw(){
    int offset_x = 0, offset_y = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (map[i][j] == '#'){
                DrawRectangle(offset_x, offset_y, block_size, block_size, BLUE);
            }
            offset_x += block_size;
        }
        offset_x = 0;
        offset_y += block_size;
    }
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

bool* Map::getMovingDirectionsForEnemy(Vector2 pos){
    int i = (int) pos.y / 50, j = (int) pos.x / 50;

    bool* dirs = new bool[4];
    dirs[0] = false;
    dirs[1] = false;
    dirs[2] = false;
    dirs[3] = false;
    if (map[i - 1][j] != '#'){
        dirs[0] = true;
    }
    if (map[i][j + 1] != '#'){
        dirs[1] = true;
    }
    if (map[i + 1][j] != '#'){
        dirs[2] = true;
    }
    if (map[i][j - 1] != '#'){
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
    if (map[j][i] == '#'){
        return true;
    }
    return false;
}

std::string Map::findPathToPlayer(Vector2 player_pos, Vector2 enemy_pos) const {
    int player_x = int(player_pos.x + 25) / 50, player_y = int(player_pos.y + 25) / 50;
    int enemy_x = int(enemy_pos.x + 25) / 50, enemy_y = int(enemy_pos.y + 25) / 50;

//    return A_star(VectorStringToCharPointerPointer(map), height, width, V2(enemy_y, enemy_x), V2(player_y, player_x));
    return "";
}

std::vector<std::string> Map::getMap() const {
    return map;
}
