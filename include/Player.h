#pragma once

#include "raylib.h"
#include "Body.h"

class Player : public Body {
public:
    void construct(Vector2 player_position, char came_from);
    ~Player();

    void update(Vector2 player_position, char came_from);
    void setLastMove();

    void move() override;
    void cancelMoves();
    void shoot();

    void addPoints(int p);
    [[nodiscard]] int getPoints() const;
    void removeOneLive();
    [[nodiscard]] int getLives() const;

    static Player* getPlayer(){
        return player;
    }
private:
    static Player* player;

    int lives;
    int points;

    std::string last_moves;
    char came_from;
};
