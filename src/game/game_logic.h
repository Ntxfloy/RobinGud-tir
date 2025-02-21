#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../../include/config.h"

class GameLogic {
public:
    static void update();
    static void startGame();
    static void startTargetMode();
    static void stopTargetMode();
    static bool isTargetMode();
    static bool isGameStarted() { return gameStarted; }
    static int getCounterValue() { return counterValue; }
    static void setCounterValue(int value) { counterValue = value; }
    
private:
    static bool gameStarted;
    static bool targetMode;
    static int timerValue;
    static int counterValue;
    static unsigned long lastTimerUpdate;
    
    static void handleTargetMode();
    static void handleGameMode();
    static void updateGameTimer();
};

#endif 