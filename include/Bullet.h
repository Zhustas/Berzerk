#pragma once

#include "raylib.h"

class Bullet {
public:
    Bullet(char direction, Vector2 position);
    ~Bullet();

    void update();
    void draw() const;
    Vector2 getBulletEndPosition();
    void setDestruction();
    bool getDestruction() const;
private:
    float speed = 0.5;
    Vector2 position;
    char direction;
    bool destroy = false;
};
