#pragma once

#include <vector>
#include <string>
#include "raylib.h"
#include "Body.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Constants.h"

class Player : public Body {
public:
    Player(Vector2 player_position, char came_from);
    ~Player();

    void update(Vector2 player_position, char came_from);
    void setLastMove();

    void move() override;
    void cancelMoves();
    void shoot();

    void addPoints(int p);
    [[nodiscard]] int getPoints() const;
    void removeOneLive();
    [[nodiscard]] int getLives() const;
    [[nodiscard]] Vector2 getPosition() const;
private:
    int lives = 3;
    int points = 0;

    std::string last_moves;
    char came_from;
};
