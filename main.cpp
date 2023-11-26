#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include "raylib.h"
#include "include/Map.h"
#include "include/Player.h"
#include "include/Enemy.h"
#include "include/Bullet.h"
#include "include/Utils.h"
#include "include/Constants.h"

void play(int& points);
void showHighScores();
void writeHighScore(const int& points, const std::string& initial);
void menu();

Player* Player::player = new Player;

int main(){
    int points = 0;
    std::string initial;

    int choice = 0;
    while (choice != 3){
        menu();
        std::cout << ">>> "; std::cin >> choice;

        switch (choice) {
            case 1:
                play(points);
                std::cout << "You scored " << points << " points." << std::endl;
                if (points > 0){
                    std::cout << "Enter your initials (3 letters): "; std::cin >> initial;
                    if (initial.size() < 3){
                        while (initial.size() != 3){
                            initial += '_';
                        }
                    }
                    writeHighScore(points, initial);
                }
                points = 0;
                break;
            case 2:
                showHighScores();
                break;
            case 3:
                std::cout << "Game closed.";
                break;
            default:
                std::cout << "Wrong input." << std:: endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

void play(int& points){
    bool level_changed = false;
    std::string current_level = getRandomMap(""), new_level;
    Map map(current_level, 'L');

    Player* player = Player::getPlayer();
    player->construct(map.getPlayerPosition(), map.getWhereCameFrom());
    std::vector<Bullet>* player_bullets;

    std::vector<Enemy> enemies;
    std::vector<Bullet>* enemy_bullets;
    std::vector<int> enemy_indexes;
    std::vector<Vector2> positions_of_enemies = map.getEnemiesPositions();

    SetTraceLogLevel(LOG_NONE);
    InitWindow(CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT, CONSTANTS::TITLE.c_str());
    player->loadImages(CONSTANTS::PLAYER_IMAGES_FILE_NAMES);

    int seed = (int) time(nullptr);
    std::default_random_engine generator(seed);
    for (int i = 0; i < positions_of_enemies.size(); i++){
        enemies.emplace_back(positions_of_enemies[i], CONSTANTS::DISTANCE_TO_MOVE_FOR_ENEMY[generator() % CONSTANTS::DISTANCE_TO_MOVE_FOR_ENEMY.size()]);
        enemies[i].determineMoving(map.getMovingDirectionsForEnemy(positions_of_enemies[i]));
        enemies[i].loadImages(CONSTANTS::ENEMY_IMAGES_FILE_NAMES);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose()){
        if (player->getLives() == 0){
            points = player->getPoints();
            break;
        }

        player->move();
        if (map.isWallBody(player->getPosition())){
            player->cancelMoves();
        }
        if (map.isOutOfMapPlayer(player->getPosition())){
            new_level = getRandomMap(current_level);
            map.load(new_level);
            current_level = new_level;
            changeLevel(player_bullets, map, enemies, positions_of_enemies);
            level_changed = true;
        }

        if (!level_changed){
            player->shoot();
            player_bullets = player->getBullets();
            for (Bullet& bullet : *player_bullets){
                if (map.isWallOrIsOutOfMapBullet(bullet.getEndPosition())){
                    bullet.setDestruction();
                } else {
                    for (Enemy& enemy : enemies){
                        if (enemy.gotHit(bullet.getEndPosition())){
                            enemy.setDestruction();
                            bullet.setDestruction();
                            player->addPoints(50);
                        }
                    }
                }
            }
            player->updateBullets();

            for (int i = 0; i < enemies.size(); i++){
                if (enemies[i].getDestruction()){
                    enemy_indexes.push_back(i);
                }
            }
            for (int index : enemy_indexes){
                enemies.erase(enemies.begin() + index);
            }
            enemy_indexes.clear();

            for (int i = 0; i < enemies.size(); i++){
                enemies[i].move();

                enemies[i].shoot(player->getPosition());
                enemy_bullets = enemies[i].getBullets();
                for (Bullet& bullet : *enemy_bullets){
                    if (map.isWallOrIsOutOfMapBullet(bullet.getEndPosition())){
                        bullet.setDestruction();
                    } else if (player->gotHit(bullet.getEndPosition())){
                        restartLevel(player_bullets, map, enemies, positions_of_enemies);
                        break;
                    }
                }
                enemies[i].updateBullets();

                if (enemies[i].touchedPlayer(player->getPosition())){
                    restartLevel(player_bullets, map, enemies, positions_of_enemies);
                }
            }
        } else {
            level_changed = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        map.draw();
        player->draw();
        for (const Enemy& enemy : enemies){
            enemy.draw();
        }
        DrawText(TextFormat("Points: %d", player->getPoints()), 60, CONSTANTS::WINDOW_HEIGHT - 40, 30, GREEN);
        DrawText(TextFormat("Lives: %d", player->getLives()), 400, CONSTANTS::WINDOW_HEIGHT - 40, 30, GREEN);

        EndDrawing();
    }
    CloseWindow();
}

void showHighScores(){
    std::ifstream file(CONSTANTS::HIGH_SCORES_FILE_NAME);

    std::vector<std::pair<int, std::string>> high_scores;
    if (file.is_open()){
        int score;
        std::string initial;
        while (file >> score >> initial){
            high_scores.emplace_back(score, initial);
        }
        std::sort(high_scores.begin(), high_scores.end(), std::greater<>());
        file.close();

        if (!high_scores.empty()){
            for (int i = 1; i <= high_scores.size(); i++){
                std::cout << "\t#" << i << "   " << high_scores[i - 1].first << ' ' << high_scores[i - 1].second << std::endl;
            }
        } else {
            std::cout << "No high scores to show." << std::endl;
        }
    } else {
        std::cout << "Failed to open " << CONSTANTS::HIGH_SCORES_FILE_NAME << '.' << std::endl;
    }
}

void menu(){
    std::cout << "1. Play" << std::endl;
    std::cout << "2. Show high scores" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void writeHighScore(const int& points, const std::string& initial){
    std::ofstream file(CONSTANTS::HIGH_SCORES_FILE_NAME, std::ios::app);
    file << points << ' ' << initial.substr(0, 3) << '\n';
    file.close();
}
