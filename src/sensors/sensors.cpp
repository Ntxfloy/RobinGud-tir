#include "sensors.h"
#include "../game/game_logic.h"
#include "../display/display.h"

const int Sensors::sensorPins[NUM_SENSORS] = {5, 17, 16, 4, 2, BUTTON_PIN};
volatile bool Sensors::sensorsTriggered[NUM_SENSORS] = {false};
volatile unsigned long Sensors::lastTriggerTime[NUM_SENSORS] = {0};

void Sensors::begin() {
    for (int i = 0; i < NUM_SENSORS; i++) {
        pinMode(sensorPins[i], INPUT_PULLUP);
        attachInterruptArg(sensorPins[i], handleInterrupt, (void*)sensorPins[i], FALLING);
    }
}

void Sensors::update() {
    static unsigned long lastResetTime = 0;
    static bool waitingReset = false;
    unsigned long now = millis();
    
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (sensorsTriggered[i]) {
            Serial.print("Датчик ");
            Serial.print(i);
            Serial.println(" сработал");
            sensorsTriggered[i] = false;
            
            if (GameLogic::isGameStarted() && !GameLogic::isTargetMode()) {
                int newValue = GameLogic::getCounterValue() + 1;
                if (newValue > 10) newValue = 10;
                GameLogic::setCounterValue(newValue);
                Display::showCounter(GameLogic::getCounterValue());
            }
            else if (GameLogic::isTargetMode()) {
                int newValue = GameLogic::getCounterValue() + 1;
                if (newValue >= 10) {
                    if (!waitingReset) {
                        GameLogic::setCounterValue(10);
                        Display::showCounter(10);
                        lastResetTime = now;
                        waitingReset = true;
                    }
                } else {
                    GameLogic::setCounterValue(newValue);
                    Display::showCounter(GameLogic::getCounterValue());
                }
            }
        }
    }
    
    // Сбрасываем счетчик через 1 секунду без delay()
    if (waitingReset && (now - lastResetTime >= 1000)) {
        GameLogic::setCounterValue(0);
        Display::showCounter(0);
        waitingReset = false;
    }
    
    // Отладка прерываний с задержкой
    static unsigned long lastDebugTime = 0;
    if (now - lastDebugTime >= 1000) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            if (sensorsTriggered[i]) {
                Serial.print("Проверка: Датчик ");
                Serial.print(i);
                Serial.println(" активен");
            }
        }
        lastDebugTime = now;
    }
}

bool Sensors::isSensorTriggered(int index) {
    if (index >= 0 && index < NUM_SENSORS) {
        bool triggered = sensorsTriggered[index];
        if (triggered) {
            sensorsTriggered[index] = false;
        }
        return triggered;
    }
    return false;
}

void IRAM_ATTR Sensors::handleInterrupt(void* arg) {
    uint32_t pin = (uint32_t)arg;
    int index = -1;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (sensorPins[i] == (int)pin) {
            index = i;
            break;
        }
    }
    if (index >= 0 && index < NUM_SENSORS) { // Проверка на выход за пределы
        unsigned long now = millis();
        static unsigned long lastTriggerTime[NUM_SENSORS] = {0};
        if (now - lastTriggerTime[index] >= 700) {
            sensorsTriggered[index] = true;
            lastTriggerTime[index] = now;
            Serial.print("Прерывание датчика ");
            Serial.println(index);
        }
    }
} 