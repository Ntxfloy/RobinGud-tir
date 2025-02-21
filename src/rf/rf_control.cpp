#include "rf_control.h"

RCSwitch RfControl::mySwitch;
unsigned long RfControl::remoteCodes[6] = {0};
bool RfControl::isPairing = false;
int RfControl::pairingIndex = 0;

void RfControl::begin() {
    pinMode(PAIRING_BUTTON_PIN, INPUT_PULLUP);
    mySwitch.enableReceive(RF_RECEIVE_PIN);
    EEPROM.begin(512);
    loadRemoteCodes();
}

void RfControl::update() {
    if (digitalRead(PAIRING_BUTTON_PIN) == LOW) {
        Display::clear();
        pairingIndex = 0;
        isPairing = true;
        Display::showCounter(1);
        Serial.println("Начата привязка пульта. Нажимайте кнопки в порядке 1-6.");
    }
    
    if (mySwitch.available()) {
        unsigned long command = mySwitch.getReceivedValue();
        if (isPairing) {
            remoteCodes[pairingIndex] = command;
            saveRemoteCodes();
            Serial.print("Привязан код: ");
            Serial.println(remoteCodes[pairingIndex]);
            pairingIndex++;
            Display::showCounter(pairingIndex + 1);
            delay(1000);
            if (pairingIndex >= 6) {
                isPairing = false;
                Display::clear();
                Serial.println("Привязка завершена.");
            }
        } else {
            Serial.print("Кнопка нажата: ");
            Serial.println(command);
            if (command == remoteCodes[0] && !GameLogic::isTargetMode()) {
                GameLogic::startGame();
            }
            else if (command == remoteCodes[1] && !GameLogic::isTargetMode()) {
                GameLogic::startTargetMode();
            }
            else if (command == remoteCodes[2]) {
                GameLogic::stopTargetMode();
            }
        }
        mySwitch.resetAvailable();
    }
}

bool RfControl::isButtonPressed(int button) {
    if (mySwitch.available()) {
        unsigned long value = mySwitch.getReceivedValue();
        mySwitch.resetAvailable();
        return value == remoteCodes[button];
    }
    return false;
}

void RfControl::saveRemoteCodes() {
    for (int i = 0; i < 6; i++) {
        EEPROM.put(EEPROM_ADDR + i * sizeof(unsigned long), remoteCodes[i]);
    }
    EEPROM.commit();
}

void RfControl::loadRemoteCodes() {
    for (int i = 0; i < 6; i++) {
        EEPROM.get(EEPROM_ADDR + i * sizeof(unsigned long), remoteCodes[i]);
    }
} 