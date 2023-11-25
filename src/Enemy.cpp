#include "../include/Enemy.h"

Enemy::Enemy(Vector2 pos, int d_to_move){
    position = pos;
    block_size = 50;
    distance_to_object_center = 25;
    speed_booster = 40;
    distance_to_move = d_to_move;
    destroy = false;
    shot = false;
    wait_for = 0;
    current_time = 0;
    walked_distance = 0.0;
    moving_index = 0;
    tint = RED;
}

Enemy::~Enemy() = default;

void Enemy::move(){
    speed = speed_booster * GetFrameTime();
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
}

void Enemy::shoot(Vector2 player){
    if (canShoot()){
        if (position.y < player.y + distance_to_object_center && player.y + distance_to_object_center < position.y + (float) block_size){
            bullets.emplace_back(determineLastMoveForShooting(player, 'y'), position);
            shot = true;

        }
        if (position.x < player.x + distance_to_object_center && player.x + distance_to_object_center < position.x + (float) block_size) {
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
    if ((position.x < player_pos.x + distance_to_object_center && player_pos.x + distance_to_object_center < position.x + (float) block_size) && (position.y < player_pos.y + distance_to_object_center && player_pos.y + distance_to_object_center < position.y + (float) block_size)){
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
