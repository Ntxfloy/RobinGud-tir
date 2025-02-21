#include "include/config.h"
#include "src/display/display.h"
#include "src/led/led_strip.h"
#include "src/rf/rf_control.h"
#include "src/sensors/sensors.h"
#include "src/game/game_logic.h"

void setup() {
    Serial.begin(115200);
    
    Display::begin();
    LedStrip::begin();
    RfControl::begin();
    Sensors::begin();
    
    Serial.println("Система инициализирована");
}

void loop() {
    GameLogic::update();
    Display::update();
    LedStrip::update();
    RfControl::update();
    Sensors::update();
} 