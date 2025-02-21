#include "game_logic.h"
#include "../display/display.h"
#include "../led/led_strip.h"
#include "../sensors/sensors.h"

bool GameLogic::gameStarted = false;
bool GameLogic::targetMode = false;
int GameLogic::timerValue = 0;
int GameLogic::counterValue = 0;
unsigned long GameLogic::lastTimerUpdate = 0;

void GameLogic::update() {
    static unsigned long lastDebugTime = 0;
    unsigned long now = millis();
    if (now - lastDebugTime >= 1000) { // Вывод каждую секунду
        Serial.print("GameLogic Update - isGameStarted: ");
        Serial.print(GameLogic::isGameStarted());
        Serial.print(", isTargetMode: ");
        Serial.println(GameLogic::isTargetMode());
        lastDebugTime = now;
    }
    updateGameTimer();
}

void GameLogic::startGame() {
    Display::clear();
    timerValue = 20;
    counterValue = 0;
    Display::showTimer(timerValue);
    Display::showCounter(counterValue);
    gameStarted = true;
    targetMode = false;
    lastTimerUpdate = millis();
    Serial.println("Игра началась!");
}

void GameLogic::startTargetMode() {
    targetMode = true;
    gameStarted = false;
    counterValue = 0;
    Display::clear();
    Display::showTimer(99);
    Display::showCounter(0);
    
    for (int i = 0; i < 6; i++) {
        LedStrip::setSegmentColor(i, LedStrip::getColor(255, 255, 255));
    }
    Serial.println("Режим мишени активирован");
}

void GameLogic::stopTargetMode() {
    targetMode = false;
    Display::clear();
    LedStrip::clear();
}

void GameLogic::handleTargetMode() {
    // Удалена лишняя логика, так как обработка теперь в Sensors::update()
}

void GameLogic::handleGameMode() {
    updateGameTimer();
}

void GameLogic::updateGameTimer() {
    if (!gameStarted || timerValue <= 0) return;
    unsigned long currentTime = millis();
    if (currentTime - lastTimerUpdate < 1000) return;
    lastTimerUpdate = currentTime;
    timerValue--;
    Display::showTimer(timerValue);
    if (timerValue == 0) {
        if (counterValue < 5) {
            LedStrip::setSegmentColor(0, LedStrip::getColor(255, 0, 0));
            delay(2000);
            LedStrip::clear();
        } else {
            LedStrip::showVictoryAnimation();
        }
        gameStarted = false;
        Display::clear();
    }
}

bool GameLogic::isTargetMode() {
    return targetMode;
} 