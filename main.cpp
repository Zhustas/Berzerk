#include <vector>
#include "raylib.h"
#include "include/HighScoresWindow.h"
#include "include/Map.h"
#include "include/Player.h"
#include "include/Enemy.h"
#include "include/Bullet.h"
#include "include/CongratulationsWindow.h"
#include "include/Utils.h"
#include "include/Constants.h"

int main(){
    HighScoresWindow highScoresWindow;

    std::string currentLevel = getRandomMap(""), newLevel;
    Map map(currentLevel, 'L');
    bool restart_level = true;

    Player player(map.getPlayerPosition(), map.getWhereCameFrom());
    std::vector<Bullet>* playerBullets;

    std::vector<Enemy> enemies;
    std::vector<int> enemyIndexes;
    std::vector<Bullet>* enemyBullets;
    std::vector<Vector2> positionsOfEnemies = map.getEnemiesPositions();

    CongratulationsWindow congratulationsWindow;

    InitWindow(CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT, CONSTANTS::TITLE.c_str());
    player.loadImages();
    Texture2D* imagesOfEnemy = getEnemyImages();

    for (int i = 0; i < positionsOfEnemies.size(); i++){
        enemies.emplace_back(positionsOfEnemies[i]);
        enemies[i].setImages(imagesOfEnemy);
        enemies[i].determineMoving(map.getMovingDirectionsForEnemy(positionsOfEnemies[i]));
    }

    while (!WindowShouldClose()){
        if (highScoresWindow.getWindowOpened()){
            if (highScoresWindow.readyToPlay()){
                highScoresWindow.setWindowOpened(false);
                map.setWindowOpened(true);
            }
        } else if (map.getWindowOpened()){
            if (player.getLives() == 0){
                map.setWindowOpened(false);
                if (player.getPoints() != 0){
                    congratulationsWindow.setWindowOpened(true);
                    congratulationsWindow.setScore(player.getPoints());
                } else {
                    highScoresWindow.setWindowOpened(true);
                }
            }
            player.move();
            if (map.isWallBody(player.getPosition())){
                player.cancelMoves();
            }
            if (map.isOutOfMapPlayer(player.getPosition())){
                newLevel = getRandomMap(currentLevel);
                map.load(newLevel);
                currentLevel = newLevel;

                player.update(map.getPlayerPosition(), map.getWhereCameFrom());
                playerBullets->clear();
            }

            player.shoot();
            playerBullets = player.getBullets();
            for (Bullet& bullet : *playerBullets){
                if (map.isWallOrIsOutOfMapBullet(bullet.getEndPosition())){
                    bullet.setDestruction();
                } else {
                    for (Enemy& enemy : enemies){
                        if (enemy.gotHit(bullet.getEndPosition())){
                            enemy.setDestruction();
                            bullet.setDestruction();
                            player.addPoints(50);
                        }
                    }
                }
            }
            player.updateBullets();

            for (int i = 0; i < enemies.size(); i++){
//                enemies[i].move();
                enemyBullets = enemies[i].getBullets();
                for (Bullet& bullet : *enemyBullets){
                    if (map.isWallOrIsOutOfMapBullet(bullet.getEndPosition())){
                        bullet.setDestruction();
                    } else if (player.gotHit(bullet.getEndPosition())){
                        restartLevel(player, map, enemies, positionsOfEnemies, imagesOfEnemy);
                        enemyIndexes.clear();
                        restart_level = true;
                        break;
                    }
                }

                if (restart_level){
                    restart_level = false;
                    break;
                }

                if (enemies[i].touchedPlayer(player.getPosition())){
                    restartLevel(player, map, enemies, positionsOfEnemies, imagesOfEnemy);
                    enemyIndexes.clear();
                    restart_level = true;
                }

                if (restart_level){
                    restart_level = false;
                    break;
                }

                if (enemies[i].getDestruction()){
                    enemyIndexes.push_back(i);
                } else {
                    enemies[i].shoot(player.getPosition());
                    enemies[i].updateBullets();
                }
            }
            for (int index : enemyIndexes){
                enemies.erase(enemies.begin() + index);
            }
            enemyIndexes.clear();
        } else if (congratulationsWindow.getWindowOpened()){
            congratulationsWindow.getInput();
            if (congratulationsWindow.wantsToCloseWindow()){
                congratulationsWindow.writeHighScores();
                congratulationsWindow.setWindowOpened(false);
                highScoresWindow.setWindowOpened(true);
                highScoresWindow.loadHighScores();
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (highScoresWindow.getWindowOpened()){
            highScoresWindow.draw();
        } else if (map.getWindowOpened()){
            map.draw();
            player.draw();
            for (const Enemy& enemy : enemies){
                enemy.draw();
            }
            DrawText(TextFormat("Points: %d", player.getPoints()), 60, CONSTANTS::WINDOW_HEIGHT - 40, 30, GREEN);
            DrawText(TextFormat("Lives: %d", player.getLives()), 400, CONSTANTS::WINDOW_HEIGHT - 40, 30, GREEN);
        } else if (congratulationsWindow.getWindowOpened()){
            congratulationsWindow.draw();
        }

        EndDrawing();
    }

    CloseWindow();
}
