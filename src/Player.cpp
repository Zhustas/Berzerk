#include <iostream>
#include "../include/Player.h"

Player::Player(Vector2 player_position, char came_from){
    this->player_position = player_position;
    this->came_from = came_from;
    setLastMove();
}

Player::~Player() = default;

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

void Player::move(){
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
    const char* image_names[] = {"player-up.png", "player-right.png", "player-down.png", "player-left.png"};

    Image current_image;
    for (int i = 0; i < 4; i++){
        current_image = LoadImage(image_names[i]);
        images[i] = LoadTextureFromImage(current_image);
    }
    UnloadImage(current_image);
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

void Player::draw(){
    DrawTexture(getPlayerTexture(), (int) player_position.x, (int) player_position.y, RAYWHITE);
    for (const Bullet& bullet : bullets){
        bullet.draw();
    }
}

void Player::shoot(){
    if (IsKeyPressed(KEY_K)){
        bullets.emplace_back(last_move, getPosition());
    }
}

void Player::update(Vector2 ply_pos, char cm_frm){
    this->player_position = ply_pos;
    this->came_from = cm_frm;
}

//void Player::update(std::vector<Enemy> enemies){
//    move();
//    shoot();
//
//    Vector2 enemy_pos, p_pos = {player_position.x + 25, player_position.y + 25};
//    for (int i = 0; i < enemies.size(); i++){
//        enemy_pos = enemies[i].getPosition();
//        if ((enemy_pos.x < p_pos.x && p_pos.x < enemy_pos.x + 50) && (enemy_pos.y < p_pos.y && p_pos.y < enemy_pos.y + 50)){
//            std::cout << "TOUCHED!";
//        }
//        // ((enemy_pos.x < end_pos.x && end_pos.x < enemy_pos.x + 50) && (enemy_pos.y < end_pos.y && end_pos.y < enemy_pos.y + 50))
//    }
//
//    std::vector<int> indexes;
//    for (int i = 0; i < bullets.size(); i++){
//        if (bullets[i].getDestruction()){
//            indexes.push_back(i);
//        }
//        bullets[i].update();
//    }
//
//    for (int index : indexes){
//        bullets.erase(bullets.begin() + index);
//    }
//}

void Player::updateBullets(){
    for (int i = 0; i < bullets.size(); i++){
        if (bullets[i].getDestruction()){
            bullets.erase(bullets.begin() + i);
            i = -1;
        } else {
            bullets[i].update();
        }
    }
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

bool Player::gotHit(Vector2 bullet_end_pos){
    return ((player_position.x < bullet_end_pos.x && bullet_end_pos.x < player_position.x + 50) && (player_position.y < bullet_end_pos.y && bullet_end_pos.y < player_position.y + 50));
}

//void Player::updateBullet(int index, char char_at_position, std::vector<Enemy>& enemies){
//    if (char_at_position == '#'){
//        bullets[index].setDestruction();
//    }
//
//    // 1 bullet, all enemies
//    Vector2 end_pos = bullets[index].getBulletEndPosition(), enemy_pos;
//    for (int i = 0; i < enemies.size(); i++){
//        enemy_pos = enemies[i].getPosition();
//        if ((enemy_pos.x < end_pos.x && end_pos.x < enemy_pos.x + 50) && (enemy_pos.y < end_pos.y && end_pos.y < enemy_pos.y + 50)){
//            bullets[index].setDestruction();
//            enemies[i].setDestruction();
//        }
//    }
//}

