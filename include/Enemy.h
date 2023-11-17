#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include "Bullet.h"
#include "Constants.h"

class Enemy {
public:
    Enemy(Vector2 pos, int d_to_move);

    ~Enemy();

    void draw() const;

    bool gotHit(Vector2 bullet_end_pos) const;
    bool touchedPlayer(Vector2 player_pos) const;

    void move();
    void shoot(Vector2 player);
    char determineLastMoveForShooting(Vector2 player, char for_what) const;
    bool canShoot() const;

    void setImages(Texture2D* imgs);

    Vector2 getPosition();

    void loadImages();

    [[nodiscard]] Texture2D getEnemyTexture() const;

    void setDestruction();
    bool getDestruction();

    void updateBullets();

    std::vector<Bullet>* getBullets();

    void determineMoving(const bool* dirs);
private:
    Vector2 position;

    Texture2D images[4];

    float speed;
    char last_move = 'D';
    int distance_to_move;

    bool destroy = false;

    std::vector<Bullet> bullets;
    bool shot = false;
    int wait_for = 0, current_time = 0;
    std::vector<int> seconds_to_wait_for_shooting = {1, 2, 3};

    std::string moving_dirs;
    float walked_distance = 0;
    int moving_index = 0;
};
