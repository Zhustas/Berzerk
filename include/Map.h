#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "raylib.h"
#include "Constants.h"

#define WALL '#'

class Map {
public:
    Map(const std::string& file_name, char came_from);
    ~Map();

    void load(const std::string& file_name);
    void draw();

    [[nodiscard]] char getWhereCameFrom() const;
    void buildWalls();

    [[nodiscard]] bool isWallBody(Vector2 position);
    bool isOutOfMapPlayer(Vector2 player_pos);
    bool isWallOrIsOutOfMapBullet(Vector2 position);

    [[nodiscard]] Vector2 getPlayerPosition() const;
    std::vector<Vector2> getEnemiesPositions();

    [[nodiscard]] bool* getMovingDirectionsForEnemy(Vector2 pos) const;
private:
    int width, height;
    int block_size;

    char came_from;

    std::vector<std::string> map;
};
