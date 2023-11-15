#pragma once

#include <vector>
#include <string>

class HighScoresWindow {
public:
    HighScoresWindow(const int& WINDOW_WIDTH, const int& WINDOW_HEIGHT);
    ~HighScoresWindow();

    void draw() const;
    void loadHighScores();
    bool readyToPlay() const;
private:
    const int WINDOW_WIDTH, WINDOW_HEIGHT;
    const char* const file_name = "high-scores.txt";
    std::vector<std::pair<int, std::string>> high_scores;
};
