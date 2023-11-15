#include "raylib.h"
#include "include/HighScoresWindow.h"
#include "include/Map.h"
#include "include/Player.h"
#include "include/Enemy.h"
#include "include/CongratulationsWIndow.h"
#include "include/Utils.h"

int main(){
    bool is_in_highscore_window = true;
    HighScoresWindow highScoresWindow(CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT);

    bool playing = false;
    std::string current_level = getRandomMap("");
    Map map(current_level, 'L');
    Player player(map.getPlayerPosition(), map.getWhereCameFrom());
    std::vector<Bullet>* playerBullets;

    std::vector<Enemy> enemies;
    std::vector<Bullet>* enemy_bullets;
    std::vector<Vector2> positions_of_enemies = map.getEnemiesPositions();

    CongratulationsWindow congratulationsWindow(CONSTANTS::WINDOW_WIDTH);
    bool in_congratulations_window = false;

    InitWindow(CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT, CONSTANTS::TITLE);
    player.loadImages();

    Texture2D* images_of_enemy = getEnemyImages();
    for (int i = 0; i < positions_of_enemies.size(); i++){
        enemies.emplace_back(positions_of_enemies[i]);
        enemies[i].determineMoving(map.getMovingDirectionsForEnemy(positions_of_enemies[i]));
        enemies[i].setImages(images_of_enemy);
    }

    while (!WindowShouldClose()){
        if (is_in_highscore_window){
            if (highScoresWindow.readyToPlay()){
                playing = true;
                is_in_highscore_window = false;
            }
        }
        if (playing){
            if (player.getLives() == 0){
                playing = false;
                if (player.getPoints() != 0){
                    in_congratulations_window = true;
                    congratulationsWindow.setScore(player.getPoints());
                } else {
                    is_in_highscore_window = true;
                }
            }
            player.move();
            if (map.isWallBody(player.getPosition())){
                player.cancelMoves();
            }
            if (map.isOutOfMapPlayer(player.getPosition())){
                std::string new_level = getRandomMap(current_level);
                map.load(new_level);
                current_level = new_level;

                player.update(map.getPlayerPosition(), map.getWhereCameFrom());
                playerBullets->clear();

                enemies.clear();
                positions_of_enemies = map.getEnemiesPositions();
                for (int i = 0; i < positions_of_enemies.size(); i++){
                    enemies.emplace_back(positions_of_enemies[i]);
                    enemies[i].setImages(images_of_enemy);
                }
            }

            player.shoot();
            player.updateBullets();
            playerBullets = player.getBullets();
            for (Bullet& bullet : *playerBullets){
                if (map.isWallOrIsOutOfMapBullet(bullet.getBulletEndPosition())){
                    bullet.setDestruction();
                }
                for (Enemy& enemy : enemies){
                    if (enemy.gotHit(bullet.getBulletEndPosition())){
                        player.addPoints(50);
                        enemy.setDestruction();
                        bullet.setDestruction();
                    }
                }
            }

            bool brk = false;
            for (int i = 0; i < enemies.size(); i++){
//                enemies[i].move(AStar(VecStr2CharDP(map.getMap()), 17, 24, Vector2ToV2(enemies[i].getPosition()),
//                                      Vector2ToV2(player.getPosition())));
                enemies[i].updateBullets();
                enemy_bullets = enemies[i].getBullets();
                for (Bullet& bullet : *enemy_bullets){
                    if (player.gotHit(bullet.getBulletEndPosition())){
                        player.removeOneLive();

                        player.update(map.getPlayerPosition(), map.getWhereCameFrom());
                        playerBullets->clear();

                        enemies.clear();
                        positions_of_enemies = map.getEnemiesPositions();
                        for (int j = 0; j < positions_of_enemies.size(); j++){
                            enemies.emplace_back(positions_of_enemies[j]);
                            enemies[j].setImages(images_of_enemy);
                        }
                        brk = true;
                        break;
                    }
                    if (map.isWallOrIsOutOfMapBullet(bullet.getBulletEndPosition())){
                        bullet.setDestruction();
                    }
                }
                if (brk){
                    break;
                }

                if (enemies[i].getDestruction()){
                    enemies.erase(enemies.begin() + i);
                    i = -1;
                }

            }
            if (brk){
                continue;
            }

            for (Enemy& enemy : enemies){
                enemy.shoot(player.getPosition());
                if (enemy.touchedPlayer(player.getPosition())){
                    player.removeOneLive();

                    player.update(map.getPlayerPosition(), map.getWhereCameFrom());
                    playerBullets->clear();

                    enemies.clear();
                    positions_of_enemies = map.getEnemiesPositions();
                    for (int i = 0; i < positions_of_enemies.size(); i++){
                        enemies.emplace_back(positions_of_enemies[i]);
                        enemies[i].setImages(images_of_enemy);
                    }
                    break;
                }
            }
        }
        if (in_congratulations_window){
            congratulationsWindow.getInput();
            if (congratulationsWindow.wantsToCloseWindow()){
                congratulationsWindow.writeHighScores();
                congratulationsWindow.setInitialsToDefault();
                highScoresWindow.loadHighScores();
                in_congratulations_window = false;
                is_in_highscore_window = true;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (is_in_highscore_window){
            highScoresWindow.draw();
        }
        if (playing){
            map.draw();
            player.draw();
            for (Enemy& enemy : enemies){
                enemy.draw();
            }
            DrawText(TextFormat("Points: %d", player.getPoints()), 50, CONSTANTS::WINDOW_HEIGHT - 35, 25, GREEN);
            DrawText(TextFormat("Lives: %d", player.getLives()), 200, CONSTANTS::WINDOW_HEIGHT - 35, 25, GREEN);
        }
        if (in_congratulations_window){
            congratulationsWindow.draw();
        }

        EndDrawing();
    }

    CloseWindow();
}
