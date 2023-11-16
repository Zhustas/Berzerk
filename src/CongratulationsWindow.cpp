#include "../include/CongratulationsWindow.h"

CongratulationsWindow::CongratulationsWindow() : WINDOW_WIDTH(CONSTANTS::WINDOW_WIDTH), WINDOW_HEIGHT(CONSTANTS::WINDOW_HEIGHT), HIGH_SCORES_FILE_NAME(CONSTANTS::HIGH_SCORES_FILE_NAME), initial("___"), is_window_opened(false),
                                                 close_button({(float) WINDOW_WIDTH - 200, (float) WINDOW_HEIGHT - 75, 175, 50}){}

CongratulationsWindow::~CongratulationsWindow() = default;

void CongratulationsWindow::draw() const {
    ClearBackground(BLACK);

    int measured_text = MeasureText("Congratulations Player", 60);
    DrawText("Congratulations Player", WINDOW_WIDTH / 2 - measured_text / 2, 10, 60, YELLOW);

    measured_text = MeasureText("You have joined the immortals", 50);
    DrawText("You have joined the immortals", WINDOW_WIDTH / 2 - measured_text / 2, 150, 50, Color(38, 150, 150, 100));

    measured_text = MeasureText("in the BERZERK hall of fame", 45);
    DrawText("in the BERZERK hall of fame", WINDOW_WIDTH / 2 - measured_text / 2, 210, 45, Color(38, 150, 150, 100));

    measured_text = MeasureText("You have joined the immortals", 60);
    DrawText("Enter your initials:", WINDOW_WIDTH / 2 - measured_text / 2 + 160, 340, 45, Color(38, 150, 150, 100));

    DrawText(initial.c_str(), WINDOW_WIDTH / 2, 400, 45, WHITE);

    DrawRectangleRec(close_button, BLACK);
    DrawRectangleLinesEx(close_button, 2, RED);
    DrawText("Close", int(close_button.x + close_button.width / 2 - 25), int(close_button.y + close_button.height / 2 - 10), 20, WHITE);
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
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), close_button) && !initial.contains('_');
}

void CongratulationsWindow::writeHighScores(){
    std::ofstream file(HIGH_SCORES_FILE_NAME, std::ios::app);
    file << score << ' ' << initial << '\n';
    file.close();
}

void CongratulationsWindow::setInitialsToDefault(){
    initial = "___";
}

void CongratulationsWindow::setWindowOpened(bool opened){
    is_window_opened = opened;
}

bool CongratulationsWindow::getWindowOpened() const {
    return is_window_opened;
}
