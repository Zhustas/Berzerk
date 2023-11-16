#include "../include/Enemy.h"

Enemy::Enemy(Vector2 pos){
    position = pos;
}

Enemy::~Enemy() = default;

void Enemy::setImages(Texture2D* imgs){
    for (int i = 0; i < 4; i++){
        images[i] = imgs[i];
    }
}

void Enemy::move(){
    speed = (float) 130 * GetFrameTime();
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

    std::cout << moving_index << ' ';
    if (walked_distance > 30){
        moving_index++;
        if (moving_index == moving_dirs.size()){
            moving_index = 0;
        }
        walked_distance = 0;
    }
//    } else if (moving_dirs[moving_index] == 'D'){
//        position.x += speed;
//        last_move = 'D';
//    } else if (moving_dirs[moving_index] == 'S'){
//        position.y += speed;
//        last_move = 'S';
//    } else {
//        position.x -= speed;
//        last_move = 'A';
//    }
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

void Enemy::loadImages(){
    const char* image_names[] = {"enemy-up.png", "enemy-right.png", "enemy-down.png", "enemy-left.png"};

    Image current_image;
    for (int i = 0; i < 4; i++){
        current_image = LoadImage(image_names[i]);
        images[i] = LoadTextureFromImage(current_image);
    }
    UnloadImage(current_image);
}

Texture2D Enemy::getEnemyTexture() const {
    if (last_move == 'W' || last_move == 'S'){
        return images[0];
    } else if (last_move == 'D' || last_move == 'A'){
        return images[1];
    }

}

void Enemy::draw() const {
    std::cout << getEnemyTexture().id << ' ';
    DrawTexture(getEnemyTexture(), (int) position.x, (int) position.y, RED);
    for (const Bullet& bullet : bullets){
        bullet.draw();
    }
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
    std::vector<int> indexes;
    for (int i = 0; i < bullets.size(); i++){
        if (bullets[i].getDestruction()){
            indexes.push_back(i);
        } else {
            bullets[i].update();
        }
    }

    for (int index : indexes){
        bullets.erase(bullets.begin() + index);
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
