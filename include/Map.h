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

    void load(const std::string& file_name);             // Load map
    void draw();                                         // Draw map

    char getWhereCameFrom() const;
    void buildWalls();

    bool isOutOfMapPlayer(Vector2 player_pos);

    Vector2 getPlayerPosition() const;                            // Get player position from the map
    std::vector<Vector2> getEnemiesPositions();             // Get positions of enemies from the map
    [[nodiscard]] bool isWallBody(Vector2 position);                // Get character at given position (when body is given)
    bool isWallOrIsOutOfMapBullet(Vector2 position);                          //

    std::string findPathToPlayer(Vector2 player_pos, Vector2 enemy_pos) const;

    [[nodiscard]] bool* getMovingDirectionsForEnemy(Vector2 pos) const;
    [[nodiscard]] std::vector<std::string> getMap() const;

    void setWindowOpened(bool opened);
    [[nodiscard]] bool getWindowOpened() const;
private:
    int width, height;
    int block_size;

    char came_from;

    std::vector<std::string> map;

    bool is_window_opened;
};
