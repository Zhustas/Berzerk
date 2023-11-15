#pragma once

#include <string>
#include <vector>
#include "raylib.h"
#include "Bullet.h"

class Enemy {
public:
    Enemy();
    Enemy(Vector2 pos);

    ~Enemy();

    bool gotHit(Vector2 bullet_end_pos) const;
    bool touchedPlayer(Vector2 player_pos) const;

    void move(const std::string& path);
    void shoot(Vector2 player);
    char determineLastMoveForShooting(Vector2 player, char for_what) const;
    bool canShoot() const;

    void setImages(Texture2D* imgs);

    Vector2 getPosition();

    void loadImages();
    void draw();
    Texture2D getEnemyTexture();

    void setDestruction();
    bool getDestruction();

    void updateBullets();

    std::vector<Bullet>* getBullets();

    void determineMoving(bool* dirs);
private:
    Vector2 position;

    Texture2D images[4];

    float speed = 0.05;
    char last_move = 'D';

    bool destroy = false;

    std::vector<Bullet> bullets;
    bool shot = false;
    int wait_for = 0, current_time = 0;
    std::vector<int> seconds_to_wait_for_shooting = {1, 2, 3};

    std::string moving_dirs;
    double walked_distance = 0;
    int moving_index = 0;
};
