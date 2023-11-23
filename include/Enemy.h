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

    bool destroy;

    bool shot;
    int wait_for;
    int current_time;

    std::string moving_dirs;
    float walked_distance;
    int moving_index;
};
