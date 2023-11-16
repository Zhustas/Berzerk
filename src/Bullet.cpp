#include "../include/Bullet.h"
#include "raylib.h"

Bullet::Bullet(char direction, Vector2 position) {
    this->direction = direction;
    this->position = {position.x + 25, position.y + 25};
}

Bullet::~Bullet() = default;

void Bullet::draw() const {
    if (direction == 'W'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x, position.y - 20), 2, RED);
    } else if (direction == 'D'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x + 20, position.y), 2, RED);
    } else if (direction == 'S'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x, position.y + 20), 2, RED);
    } else if (direction == 'A'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x - 20, position.y), 2, RED);
    }
}

void Bullet::update(){
    speed = 400 * GetFrameTime();
    if (direction == 'W'){
        position.y -= speed;
    } else if (direction == 'D'){
        position.x += speed;
    } else if (direction == 'S'){
        position.y += speed;
    } else if (direction == 'A'){
        position.x -= speed;
    }
}

Vector2 Bullet::getEndPosition(){
    if (direction == 'W'){
        return {position.x, position.y - 20};
    } else if (direction == 'D'){
        return {position.x + 20, position.y};
    } else if (direction == 'S'){
        return {position.x, position.y + 20};
    } else if (direction == 'A'){
        return {position.x - 20, position.y};
    }
}

void Bullet::setDestruction(){
    destroy = true;
}

bool Bullet::getDestruction() const {
    return destroy;
}
