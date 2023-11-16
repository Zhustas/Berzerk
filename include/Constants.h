#pragma once

#include <vector>
#include <string>

namespace CONSTANTS {
    const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 850;
    const std::string TITLE = "Berzerk";

    const std::vector<std::string> LEVELS = {"level1.txt", "level2.txt", "level3.txt", "level4.txt"};

    const int MAP_WIDTH = 24, MAP_HEIGHT = 17, BLOCK_SIZE = 50;

    const std::vector<std::string> PLAYER_IMAGES_FILE_NAMES = {"player-up.png", "player-right.png", "player-down.png", "player-left.png"};
    const std::vector<std::string> ENEMY_IMAGES_FILE_NAMES = {"enemy-up.png", "enemy-right.png", "enemy-down.png", "enemy-left.png"};

    const std::vector<int> SECONDS_TO_WAIT_FOR_ENEMY_TO_SHOOT_AGAIN = {1, 2, 3};

    const std::string HIGH_SCORES_FILE_NAME = "high-scores.txt";
}
