#pragma once

#include <string>

class CongratulationsWindow {
public:
    explicit CongratulationsWindow(const int& WINDOW_WIDTH);
    ~CongratulationsWindow();

    void draw() const;
    void setScore(int score);
    void getInput();
    bool wantsToCloseWindow();
    void writeHighScores();

    void setInitialsToDefault();
private:
    const int WINDOW_WIDTH;
    int score;
    std::string initial = "___";
    const char* file_name = "high-scores.txt";
};
