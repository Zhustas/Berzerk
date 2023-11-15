#include <iostream>
#include <fstream>
#include <algorithm>
#include "raylib.h"
#include "../include/HighScoresWindow.h"

HighScoresWindow::HighScoresWindow(const int& W_WIDTH, const int& W_HEIGHT) : WINDOW_WIDTH(W_WIDTH), WINDOW_HEIGHT(W_HEIGHT){
    loadHighScores();
    std::sort(high_scores.begin(), high_scores.end(), std::greater<>());
}

HighScoresWindow::~HighScoresWindow() = default;

void HighScoresWindow::draw() const {
    ClearBackground(BLACK);

    int font_size = 45, measured_text = MeasureText("High Scores", font_size), h_x = WINDOW_WIDTH / 2 - measured_text / 2;
    DrawText("High Scores", h_x, 10, font_size, GREEN);
    DrawLineEx({0, 75}, {(float) WINDOW_WIDTH, 75}, 5, WHITE);

    font_size = 50;
    for (int i = 0; i < high_scores.size(); i++){
        DrawText(TextFormat("%d", i + 1), h_x - 60, 90 + 50 * i, font_size, RED);
        DrawText(TextFormat("%d", high_scores[i].first), h_x + 30, 90 + 50 * i, font_size, YELLOW);
        measured_text = MeasureText(TextFormat("%d", high_scores[i].first), font_size);
        DrawText(high_scores[i].second.c_str(), h_x + 30 + measured_text + 70, 90 + 50 * i, font_size, PURPLE);
        if (i == 12){
            break;
        }
    }
    DrawLineEx({0, float(WINDOW_HEIGHT - 100)}, {(float) WINDOW_WIDTH, float(WINDOW_HEIGHT - 100)}, 5, WHITE);
}

void HighScoresWindow::loadHighScores(){
    std::ifstream file(file_name);

    if (file.is_open()){
        high_scores.clear();

        int score;
        std::string initial;
        while (file >> score >> initial){
            high_scores.emplace_back(score, initial);
        }
        file.close();
    } else {
        std::cout << "Failed to open " << file_name << std::endl;
    }
}

bool HighScoresWindow::readyToPlay() const {
    return IsKeyPressed(KEY_L);
}
