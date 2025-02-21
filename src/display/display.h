#ifndef DISPLAY_H
#define DISPLAY_H

#include "../../include/config.h"
#include "../rf/rf_control.h"
#include "../game/game_logic.h"

class Display {
public:
    static void begin();
    static void update();
    static void showTimer(int value);    // Для display1
    static void showCounter(int value);  // Для display2
    static void clear();
    static void updateSnowEffect();

private:
    static MD_Parola display1;
    static MD_Parola display2;
    static const uint8_t MATRIX_ROWS = 8;
    static const uint8_t MATRIX_COLS = 16;
    static const uint8_t MAX_ACTIVE_PIXELS = (MATRIX_ROWS * MATRIX_COLS * 44) / 100;
    static unsigned long lastSnowUpdate;
};

#endif 