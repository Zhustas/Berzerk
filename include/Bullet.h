#pragma once

#include "raylib.h"

class Bullet {
public:
    Bullet(char direction, Vector2 position);
    ~Bullet();

    void update();
    void draw() const;

    Vector2 getEndPosition();

    void setDestruction();
    [[nodiscard]] bool getDestruction() const;
private:
    float speed;
    Vector2 position;
    char direction;
    bool destroy = false;
};
