#ifndef RF_CONTROL_H
#define RF_CONTROL_H

#include "../../include/config.h"
#include "../display/display.h"
#include "../game/game_logic.h"

class RfControl {
public:
    static bool isPairing;
    static void begin();
    static void update();
    static void startPairing();
    static void handlePairing();
    static bool isButtonPressed(int button);
    
private:
    static RCSwitch mySwitch;
    static unsigned long remoteCodes[6];
    static int pairingIndex;
    
    static void saveRemoteCodes();
    static void loadRemoteCodes();
};

#endif 