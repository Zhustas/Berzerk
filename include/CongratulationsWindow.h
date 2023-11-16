#pragma once

#include <fstream>
#include <string>
#include "raylib.h"
#include "Constants.h"

class CongratulationsWindow {
public:
    CongratulationsWindow();
    ~CongratulationsWindow();

    void draw() const;

    void setScore(int score);
    void getInput();
    bool wantsToCloseWindow();
    void writeHighScores();

    void setInitialsToDefault();

    void setWindowOpened(bool opened);
    [[nodiscard]] bool getWindowOpened() const;
private:
    const int WINDOW_WIDTH, WINDOW_HEIGHT;
    const std::string HIGH_SCORES_FILE_NAME;

    int score;
    std::string initial;

    Rectangle close_button;

    bool is_window_opened;
};
