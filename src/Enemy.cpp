#include "../include/Enemy.h"

Enemy::Enemy(Vector2 pos, int d_to_move){
    position = pos;
    distance_to_move = d_to_move;
    tint = RED;
}

Enemy::~Enemy() = default;

void Enemy::move(){
    speed = (float) 40 * GetFrameTime();
    if (moving_dirs[moving_index] == 'W') {
        position.y -= speed;
        last_move = 'W';
        walked_distance += speed;
    }
    if (moving_dirs[moving_index] == 'D'){
        position.x += speed;
        last_move = 'D';
        walked_distance += speed;
    }
    if (moving_dirs[moving_index] == 'S'){
        position.y += speed;
        last_move = 'S';
        walked_distance += speed;
    }
    if (moving_dirs[moving_index] == 'A') {
        position.x -= speed;
        last_move = 'A';
        walked_distance += speed;
    }

    if (walked_distance > (float) distance_to_move){
        moving_index++;
        if (moving_index == moving_dirs.size()){
            moving_index = 0;
        }
        walked_distance = 0;
    }
}

void Enemy::determineMoving(const bool* dirs){
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

    for (int i = 0; i < moving_dirs.size() / 2; i++){

    }
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
            int seed = (int) time(nullptr);
            std::default_random_engine generator(seed);

            wait_for = CONSTANTS::SECONDS_TO_WAIT_FOR_ENEMY_TO_SHOOT_AGAIN[generator() % (int) CONSTANTS::SECONDS_TO_WAIT_FOR_ENEMY_TO_SHOOT_AGAIN.size()];
            current_time = (int) time(nullptr);
        }
    }
}

bool Enemy::canShoot() const {
    if (time(nullptr) - current_time >= wait_for){
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

void Enemy::setDestruction(){
    destroy = true;
}

bool Enemy::getDestruction() const {
    return destroy;
}
