#include "../include/Player.h"

Player::Player(Vector2 player_position, char came_from){
    this->player_position = player_position;
    this->came_from = came_from;
    setLastMove();
}

Player::~Player() = default;

void Player::draw(){
    DrawTexture(getPlayerTexture(), (int) player_position.x, (int) player_position.y, RAYWHITE);
    for (const Bullet& bullet : bullets){
        bullet.draw();
    }
}

Texture2D Player::getPlayerTexture(){
    if (last_move == 'W'){
        return images[0];
    } else if (last_move == 'D'){
        return images[1];
    } else if (last_move == 'S'){
        return images[2];
    }
    return images[3];
}

void Player::setLastMove(){
    if (came_from == 'L'){
        last_move = 'D';
    } else if (came_from == 'D'){
        last_move = 'W';
    } else if (came_from == 'U'){
        last_move = 'S';
    }
    last_move = 'A';
}

void Player::shoot(){
    if (IsKeyPressed(KEY_K)){
        bullets.emplace_back(last_move, getPosition());
    }
}

void Player::move(){
    speed = (float) 130 * GetFrameTime();
    last_moves = "";
    if (IsKeyDown('W')){
        player_position.y -= speed;
        last_moves += 'W';
        last_move = 'W';
    }
    if (IsKeyDown('D')){
        player_position.x += speed;
        last_moves += 'D';
        last_move = 'D';
    }
    if (IsKeyDown('S')){
        player_position.y += speed;
        last_moves += 'S';
        last_move = 'S';
    }
    if (IsKeyDown('A')){
        player_position.x -= speed;
        last_moves += 'A';
        last_move = 'A';
    }
}

void Player::cancelMoves(){
    int last_moves_size = (int) last_moves.size();
    for (int i = 0; i < last_moves_size; i++){
        if (last_moves[last_moves_size - 1 - i] == 'W'){
            player_position.y += speed;
        } else if (last_moves[last_moves_size - 1 - i] == 'D'){
            player_position.x -= speed;
        } else if (last_moves[last_moves_size - 1 - i] == 'S'){
            player_position.y -= speed;
        } else {
            player_position.x += speed;
        }
    }
}

Vector2 Player::getPosition() const {
    return player_position;
}

void Player::loadImages(){
    Image current_image;
    for (int i = 0; i < 4; i++){
        current_image = LoadImage(CONSTANTS::PLAYER_IMAGES_FILE_NAMES[i].c_str());
        images[i] = LoadTextureFromImage(current_image);
        UnloadImage(current_image);
    }
}

void Player::update(Vector2 ply_pos, char cm_frm){
    this->player_position = ply_pos;
    this->came_from = cm_frm;
}

void Player::updateBullets(){
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

bool Player::gotHit(Vector2 bullet_end_pos) const {
    return ((player_position.x < bullet_end_pos.x && bullet_end_pos.x < player_position.x + 50) && (player_position.y < bullet_end_pos.y && bullet_end_pos.y < player_position.y + 50));
}


std::vector<Bullet>* Player::getBullets(){
    return &bullets;
}

void Player::addPoints(int p){
    points += p;
}

int Player::getPoints() const {
    return points;
}

void Player::removeOneLive(){
    lives--;
}

int Player::getLives() const {
    return lives;
}
