#include <utility>

#include "../include/Enemy.h"
#include "../include/Utils.h"

Enemy::Enemy() = default;

Enemy::Enemy(Vector2 pos){
    srand(time(nullptr));
    position = pos;
}

Enemy::~Enemy() = default;

void Enemy::setImages(Texture2D* imgs){
    for (int i = 0; i < 4; i++){
        images[i] = imgs[i];
    }
}

void Enemy::determineMoving(bool* dirs){
    if (dirs[0]){
        moving_dirs += "WS";
    }
    if (dirs[1]){
        moving_dirs += "DA";
    }
    if (dirs[2]){
        moving_dirs += "SW";
    }
    if (dirs[3]){
        moving_dirs += "AD";
    }
}

void Enemy::loadImages(){
    const char* image_names[] = {"enemy-up.png", "enemy-right.png", "enemy-down.png", "enemy-left.png"};

    Image current_image;
    for (int i = 0; i < 4; i++){
        current_image = LoadImage(image_names[i]);
        images[i] = LoadTextureFromImage(current_image);
    }
    UnloadImage(current_image);
}

Texture2D Enemy::getEnemyTexture(){
    if (last_move == 'W'){
        return images[0];
    } else if (last_move == 'D'){
        return images[1];
    } else if (last_move == 'S'){
        return images[2];
    }
    return images[3];
}

void Enemy::draw(){
    DrawTexture(getEnemyTexture(), (int) position.x, (int) position.y, RED);
    for (const Bullet& bullet : bullets){
        bullet.draw();
    }
}

void Enemy::move(const std::string& path){
    char first = path[0];

    if (first == 'U'){
        position.y -= speed;
        last_move = 'W';
    } else if (first == 'R'){
        position.x += speed;
        last_move = 'D';
    } else if (first == 'D'){
        position.y += speed;
        last_move = 'S';
    } else {
        position.x -= speed;
        last_move = 'A';
    }

    /*if (moving_dirs[moving_index] == 'W'){
        position.y -= speed;
        last_move = 'W';
    } else if (moving_dirs[moving_index] == 'D'){
        position.x += speed;
        last_move = 'D';
    } else if (moving_dirs[moving_index] == 'S'){
        position.y += speed;
        last_move = 'S';
    } else {
        position.x -= speed;
        last_move = 'A';
    }

    walked_distance += speed;
    std::cout << walked_distance << std::endl;
    if (walked_distance >= 30){
        if (moving_index + 1 == moving_dirs.size()){
            moving_index = 0;
        } else {
            moving_index++;
        }
        std::cout << "Here";
        walked_distance = 0;
    }*/
}

Vector2 Enemy::getPosition(){
    return position;
}

void Enemy::setDestruction(){
    destroy = true;
}

bool Enemy::getDestruction(){
    return destroy;
}

bool Enemy::canShoot() const {
    if (time(nullptr) - current_time >= wait_for){
        return true;
    }
    return false;
}

void Enemy::shoot(Vector2 player){
    if (canShoot()){
        if (position.y < player.y + 25 && player.y + 25 < position.y + 50){
            bullets.emplace_back(determineLastMoveForShooting(player, 'y'), position);
            shot = true;

        }
        if (position.x < player.x + 25 && player.x + 25 < position.x + 50) {
            bullets.emplace_back(determineLastMoveForShooting(player, 'x'), position);
            shot = true;
        }
        if (shot){
            wait_for = seconds_to_wait_for_shooting[rand() % (int) seconds_to_wait_for_shooting.size()];
            current_time = (int) time(nullptr);
        }
    }
}

char Enemy::determineLastMoveForShooting(Vector2 player, char for_what) const {
    if (for_what == 'y'){
        if (player.x < position.x){
            return 'A';
        } else {
            return 'D';
        }
    } else {
        if (player.y < position.y){
            return 'W';
        } else {
            return 'S';
        }
    }
}

void Enemy::updateBullets(){
    for (int i = 0; i < bullets.size(); i++){
        bullets[i].update();
        if (bullets[i].getDestruction()){
            bullets.erase(bullets.begin() + i);
            i = -1;
        }
    }
}

std::vector<Bullet>* Enemy::getBullets(){
    return &bullets;
}

bool Enemy::gotHit(Vector2 bullet_end_pos) const {
    if ((position.x < bullet_end_pos.x && bullet_end_pos.x < position.x + 50) && (position.y < bullet_end_pos.y && bullet_end_pos.y < position.y + 50)){
        return true;
    }
    return false;
}

bool Enemy::touchedPlayer(Vector2 player_pos) const {
    if ((position.x < player_pos.x + 25 && player_pos.x + 25 < position.x + 50) && (position.y < player_pos.y + 25 && player_pos.y + 25 < position.y + 50)){
        return true;
    }
    return false;
}
