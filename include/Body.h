#pragma once

#include <vector>
#include <string>
#include "raylib.h"
#include "Bullet.h"

class Body {
public:
    virtual void move() = 0;

    void draw() const;
    [[nodiscard]] Texture2D getTexture() const;
    void loadImages(const std::vector<std::string>& image_paths);

    void updateBullets();
    [[nodiscard]] std::vector<Bullet>* getBullets();
    [[nodiscard]] bool gotHit(Vector2 bullet_end_pos) const;

    [[nodiscard]] Vector2 getPosition() const;
protected:
    float speed;
    float speed_booster;
    Vector2 position;
    int block_size;
    char last_move;

    Texture2D images[4];
    Color tint;

    std::vector<Bullet> bullets;
};
