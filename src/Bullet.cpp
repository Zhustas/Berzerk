#include "../include/Bullet.h"

Bullet::Bullet(char direction, Vector2 pos) {
    this->direction = direction;
    this->position = {pos.x + 25, pos.y + 25};
    speed_booster = 400;
    bullet_length = 20;
    destroy = false;
}

Bullet::~Bullet() = default;

void Bullet::draw() const {
    if (direction == 'W'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x, position.y - bullet_length), 2, RED);
    } else if (direction == 'D'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x + bullet_length, position.y), 2, RED);
    } else if (direction == 'S'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x, position.y + bullet_length), 2, RED);
    } else if (direction == 'A'){
        DrawLineEx(Vector2(position.x, position.y), Vector2(position.x - bullet_length, position.y), 2, RED);
    }
}

void Bullet::update(){
    speed = speed_booster * GetFrameTime();
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
        return {position.x, position.y - bullet_length};
    } else if (direction == 'D'){
        return {position.x + bullet_length, position.y};
    } else if (direction == 'S'){
        return {position.x, position.y + bullet_length};
    } else if (direction == 'A'){
        return {position.x - bullet_length, position.y};
    }
}

void Bullet::setDestruction(){
    destroy = true;
}

bool Bullet::getDestruction() const {
    return destroy;
}
