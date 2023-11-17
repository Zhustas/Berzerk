#pragma once

#include <vector>
#include <string>
#include "raylib.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Constants.h"

class Player {
public:
    Player(Vector2 player_position, char came_from);
    ~Player();

    void update(Vector2 player_position, char came_from);
    void setLastMove();

    void move();
    void cancelMoves();

    void loadImages();
    void draw();

    void updateBullets();
    void shoot();
    [[nodiscard]] bool gotHit(Vector2 bullet_end_pos) const;

    void addPoints(int p);
    [[nodiscard]] int getPoints() const;
    void removeOneLive();
    [[nodiscard]] int getLives() const;


    [[nodiscard]] Vector2 getPosition() const;
    std::vector<Bullet>* getBullets();
    [[nodiscard]] Texture2D getPlayerTexture();
private:
    int lives = 3;
    int points = 0;
    float speed;
    Vector2 player_position;

    std::string last_moves;
    char last_move = 'D';
    char came_from;
    Texture2D images[4];

    std::vector<Bullet> bullets;
};
