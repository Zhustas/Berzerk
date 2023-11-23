#include "../include/Player.h"

Player::Player(Vector2 player_position, char came_from){
    this->position = player_position;
    this->came_from = came_from;
    tint = RAYWHITE;
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

void Player::shoot(){
    if (IsKeyPressed(KEY_K)){
        bullets.emplace_back(last_move, getPosition());
    }
}

void Player::move(){
    speed = (float) 130 * GetFrameTime();
    last_moves = "";
    if (IsKeyDown('W')){
        position.y -= speed;
        last_moves += 'W';
        last_move = 'W';
    }
    if (IsKeyDown('D')){
        position.x += speed;
        last_moves += 'D';
        last_move = 'D';
    }
    if (IsKeyDown('S')){
        position.y += speed;
        last_moves += 'S';
        last_move = 'S';
    }
    if (IsKeyDown('A')){
        position.x -= speed;
        last_moves += 'A';
        last_move = 'A';
    }
}

void Player::cancelMoves(){
    int last_moves_size = (int) last_moves.size();
    for (int i = 0; i < last_moves_size; i++){
        if (last_moves[last_moves_size - 1 - i] == 'W'){
            position.y += speed;
        } else if (last_moves[last_moves_size - 1 - i] == 'D'){
            position.x -= speed;
        } else if (last_moves[last_moves_size - 1 - i] == 'S'){
            position.y -= speed;
        } else {
            position.x += speed;
        }
    }
}

Vector2 Player::getPosition() const {
    return position;
}

void Player::update(Vector2 ply_pos, char cm_frm){
    this->position = ply_pos;
    this->came_from = cm_frm;
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
