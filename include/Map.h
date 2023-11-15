#pragma once

#include <vector>
#include <string>
#include "raylib.h"

#define WALL '#'

class Map {
public:
    Map();
    explicit Map(const std::string& file_name, char came_from);
    ~Map();

    void load(const std::string& file_name);             // Load map
    void draw();                                         // Draw map

    char getWhereCameFrom() const;
    void buildWalls();

    bool isOutOfMapPlayer(Vector2 player_pos);

    Vector2 getPlayerPosition() const;                            // Get player position from the map
    std::vector<Vector2> getEnemiesPositions();             // Get positions of enemies from the map
    bool isWallBody(Vector2 position);                // Get character at given position (when body is given)
    bool isWallOrIsOutOfMapBullet(Vector2 position);                          //
    std::vector<std::string> map;
    std::string findPathToPlayer(Vector2 player_pos, Vector2 enemy_pos) const;

    bool* getMovingDirectionsForEnemy(Vector2 pos);
    std::vector<std::string> getMap() const;
private:
    int width = 24, height = 17;
    int block_size = 50;
    char came_from;
};
