#include <iostream>
#include <fstream>
#include "../include/CongratulationsWIndow.h"
#include "raylib.h"

CongratulationsWindow::CongratulationsWindow(const int& W_WIDTH) : WINDOW_WIDTH(W_WIDTH){}

CongratulationsWindow::~CongratulationsWindow() = default;

void CongratulationsWindow::draw() const {
    ClearBackground(BLACK);

    int measured_text = MeasureText("Congratulations Player", 60);
    DrawText("Congratulations Player", WINDOW_WIDTH / 2 - measured_text / 2, 10, 60, YELLOW);

    measured_text = MeasureText("You have joined the immortals", 50);
    DrawText("You have joined the immortals", WINDOW_WIDTH / 2 - measured_text / 2, 150, 50, Color(27, 87, 87, 100));

    measured_text = MeasureText("in the BERZERK hall of fame", 45);
    DrawText("in the BERZERK hall of fame", WINDOW_WIDTH / 2 - measured_text / 2, 210, 45, Color(27, 87, 87, 100));

    measured_text = MeasureText("You have joined the immortals", 60);
    DrawText("Enter your initials:", WINDOW_WIDTH / 2 - measured_text / 2 + 160, 340, 45, Color(27, 87, 87, 100));

    DrawText(initial.c_str(), WINDOW_WIDTH / 2, 400, 45, WHITE);

    measured_text = MeasureText("You have joined the immortals", 50);
    DrawText("Enter and then press ENTER to store it.", WINDOW_WIDTH / 2 - measured_text / 2, 550, 40, GREEN);
}

void CongratulationsWindow::setScore(int scr) {
    score = scr;
}

void CongratulationsWindow::getInput(){
    int c = GetCharPressed();

    if (c != 0){
        if (initial[0] == '_'){
            initial[0] = (char) c;
        } else if (initial[1] == '_'){
            initial[1] = (char) c;
        } else if (initial[2] == '_'){
            initial[2] = (char) c;
        }
    }
}

bool CongratulationsWindow::wantsToCloseWindow(){
    if (!initial.contains('_')){
        return IsKeyPressed(KEY_ENTER);
    }
    return false;
}

void CongratulationsWindow::writeHighScores(){
    std::ofstream file(file_name, std::ios::app);
    file << score << ' ' << initial << '\n';
    file.close();
}

void CongratulationsWindow::setInitialsToDefault(){
    initial = "___";
}
