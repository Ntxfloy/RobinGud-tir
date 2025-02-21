#ifndef LED_STRIP_H
#define LED_STRIP_H

#include "../../include/config.h"

class LedStrip {
public:
    static void begin();
    static void update();
    static void updateFrameLighting();
    static void setSegmentColor(int segment, uint32_t color);
    static void showVictoryAnimation();
    static void clear();
    static uint32_t getColor(uint8_t r, uint8_t g, uint8_t b);

private:
    static Adafruit_NeoPixel strip;
    static uint8_t frameHue;
    static const int LED_SEGMENTS[6][4];
    static unsigned long frameUpdateTime;
};

#endif 