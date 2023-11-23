#pragma once

#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include "Bullet.h"
#include "Constants.h"
#include "Body.h"

class Enemy : public Body {
public:
    Enemy(Vector2 pos, int d_to_move);

    ~Enemy();

    [[nodiscard]] bool touchedPlayer(Vector2 player_pos) const;

    void move() override;
    void determineMoving(const bool* dirs);

    void shoot(Vector2 player);
    [[nodiscard]] bool canShoot() const;
    [[nodiscard]] char determineLastMoveForShooting(Vector2 player, char for_what) const;

    void setDestruction();
    [[nodiscard]] bool getDestruction() const;
private:
    int distance_to_move;

    bool destroy = false;

    bool shot = false;
    int wait_for = 0, current_time = 0;
    std::vector<int> seconds_to_wait_for_shooting = {1, 2, 3};

    std::string moving_dirs;
    float walked_distance = 0;
    int moving_index = 0;
};
