#include "display.h"

MD_Parola Display::display1(MD_MAX72XX::FC16_HW, DATA_PIN1, CLK_PIN1, CS_PIN1, MAX_DEVICES);
MD_Parola Display::display2(MD_MAX72XX::FC16_HW, DATA_PIN2, CLK_PIN2, CS_PIN2, MAX_DEVICES);
unsigned long Display::lastSnowUpdate = 0;

void Display::begin() {
    display1.begin();
    display1.setIntensity(5);
    display1.displayClear();
    
    display2.begin();
    display2.setIntensity(5);
    display2.displayClear();
}

void Display::update() {
    static unsigned long lastDebugTime = 0;
    unsigned long now = millis();
    if (now - lastDebugTime >= 1000) { // Вывод каждую секунду
        Serial.print("isGameStarted: ");
        Serial.print(GameLogic::isGameStarted());
        Serial.print(", isPairing: ");
        Serial.print(RfControl::isPairing);
        Serial.print(", isTargetMode: ");
        Serial.println(GameLogic::isTargetMode());
        lastDebugTime = now;
    }
    
    if (!GameLogic::isGameStarted() && !RfControl::isPairing && !GameLogic::isTargetMode()) {
        updateSnowEffect();
    }
}

void Display::showTimer(int value) {
    display1.setTextAlignment(PA_CENTER);
    display1.print(value);
}

void Display::showCounter(int value) {
    char scoreStr[3];
    sprintf(scoreStr, "%02d", value);
    display2.setTextAlignment(PA_CENTER);
    display2.print(scoreStr);
}

void Display::clear() {
    display1.displayClear();
    display2.displayClear();
}

void Display::updateSnowEffect() {
    if (millis() - lastSnowUpdate < 200) return;
    lastSnowUpdate = millis();

    uint8_t display1Buffer[MATRIX_ROWS][2] = {0};
    uint8_t display2Buffer[MATRIX_ROWS][2] = {0};
    int activePixels = 0;

    while (activePixels < MAX_ACTIVE_PIXELS) {
        int row = random(MATRIX_ROWS);
        int col = random(MATRIX_COLS);
        int matrix = col / 8;
        int localCol = col % 8;

        if (!(display1Buffer[row][matrix] & (1 << localCol))) {
            display1Buffer[row][matrix] |= (1 << localCol);
            activePixels++;
        }

        row = random(MATRIX_ROWS);
        col = random(MATRIX_COLS);
        matrix = col / 8;
        localCol = col % 8;

        if (!(display2Buffer[row][matrix] & (1 << localCol))) {
            display2Buffer[row][matrix] |= (1 << localCol);
            activePixels++;
        }
    }

    display1.displayClear();
    display2.displayClear();

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < 8; col++) {
            if (display1Buffer[row][0] & (1 << col)) {
                display1.getGraphicObject()->setPoint(row, col, true);
            }
            if (display1Buffer[row][1] & (1 << col)) {
                display1.getGraphicObject()->setPoint(row, col + 8, true);
            }
            if (display2Buffer[row][0] & (1 << col)) {
                display2.getGraphicObject()->setPoint(row, col, true);
            }
            if (display2Buffer[row][1] & (1 << col)) {
                display2.getGraphicObject()->setPoint(row, col + 8, true);
            }
        }
    }
} 