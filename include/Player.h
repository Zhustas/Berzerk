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

//    void update(std::vector<Enemy> enemies);
    void update(Vector2 player_position, char came_from);

    void move();
    void shoot();
    void draw();
    void loadImages();
    void updateBullets();
    bool gotHit(Vector2 bullet_end_pos);

    void addPoints(int p);
    int getPoints() const;
    void removeOneLive();
    int getLives() const;

    void setLastMove();

    Vector2 getPosition() const;
    void cancelMoves();

    std::vector<Bullet>* getBullets();
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

    Texture2D getPlayerTexture();
};
