#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "raylib.h"
#include "Constants.h"

class HighScoresWindow {
public:
    HighScoresWindow();
    ~HighScoresWindow();

    void draw() const;
    void loadHighScores();
    [[nodiscard]] bool readyToPlay() const;

    void setWindowOpened(bool opened);
    [[nodiscard]] bool getWindowOpened() const;
private:
    const int WINDOW_WIDTH, WINDOW_HEIGHT;
    const std::string HIGH_SCORES_FILE_NAME;

    std::vector<std::pair<int, std::string>> high_scores;

    bool is_window_opened;
};
