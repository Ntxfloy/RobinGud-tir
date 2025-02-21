#ifndef SENSORS_H
#define SENSORS_H

#include "../../include/config.h"

class Sensors {
public:
    static void begin();
    static void update();
    static bool isSensorTriggered(int index);
    
private:
    static const int NUM_SENSORS = 6;
    static const int sensorPins[NUM_SENSORS];
    static volatile bool sensorsTriggered[NUM_SENSORS];
    static volatile unsigned long lastTriggerTime[NUM_SENSORS];
    
    static void IRAM_ATTR handleInterrupt(void* arg);
};

#endif 