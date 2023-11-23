#pragma once

#include "raylib.h"

class Command {
public:
    virtual void execute(float speed) = 0;
};

class Position {
public:
    Position(Vector2 pos) : position(pos) {}

    void goUp(float speed){
        position.y -= speed;
    }
    void goRight(float speed){
        position.x += speed;
    }
    void goDown(float speed){
        position.y += speed;
    }
    void goLeft(float speed){
        position.x -= speed;
    }
private:
    Vector2 position;
};

class MoveUpCommand : public Command {
public:
    MoveUpCommand(Position& pos) : position(pos) {}
    void execute(float speed) override {
        position.goUp(speed);
    }
private:
    Position& position;
};

class MoveRightCommand : public Command {
public:
    MoveRightCommand(Position& pos) : position(pos) {}
    void execute(float speed) override {
        position.goRight(speed);
    }
private:
    Position& position;
};

class MoveDownCommand : public Command {
public:
    MoveDownCommand(Position& pos) : position(pos) {}
    void execute(float speed) override {
        position.goDown(speed);
    }
private:
    Position& position;
};

class MoveLeftCommand : public Command {
public:
    MoveLeftCommand(Position& pos) : position(pos) {}
    void execute(float speed) override {
        position.goLeft(speed);
    }
private:
    Position& position;
};

class Move {
    Move(Command& up, Command& right, Command& down, Command& left) : move_up(up), move_right(right), move_down(down), move_left(left) {}
    void moveUp(float speed){
        move_up.execute(speed);
    }
    void moveRight(float speed){
        move_right.execute(speed);
    }
    void moveDown(float speed){
        move_down.execute(speed);
    }
    void moveLeft(float speed){
        move_left.execute(speed);
    }
private:
    Command& move_up;
    Command& move_right;
    Command& move_down;
    Command& move_left;
};
