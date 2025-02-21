#include "led_strip.h"

Adafruit_NeoPixel LedStrip::strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
uint8_t LedStrip::frameHue = 0;
unsigned long LedStrip::frameUpdateTime = 0;

const int LedStrip::LED_SEGMENTS[6][4] = {
    {0, 1, 2, 3},
    {20, 21, 22, 23},
    {40, 41, 42, 43},
    {60, 61, 62, 63},
    {80, 81, 82, 83},
    {100, 101, 102, 103}
};

void LedStrip::begin() {
    strip.begin();
    strip.show();
}

void LedStrip::update() {
    // Регулярное обновление состояния ленты
}

void LedStrip::updateFrameLighting() {
    if (millis() - frameUpdateTime < 50) return;
    frameUpdateTime = millis();

    frameHue += 4;
    for (int i = 0; i < NUM_LEDS; i++) {
        bool isHole = false;
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                if (i == LED_SEGMENTS[j][k]) {
                    isHole = true;
                    break;
                }
            }
            if (isHole) break;
        }
        if (!isHole) {
            strip.setPixelColor(i, strip.ColorHSV(frameHue * 256, 255, 255));
        }
    }
    strip.show();
}

void LedStrip::setSegmentColor(int segment, uint32_t color) {
    if (segment >= 0 && segment < 6) {
        for (int led = 0; led < 4; led++) {
            strip.setPixelColor(LED_SEGMENTS[segment][led], color);
        }
        strip.show();
    }
}

void LedStrip::showVictoryAnimation() {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < NUM_LEDS; j++) {
            strip.setPixelColor(j, strip.Color(random(0, 233), random(0, 222), random(0, 229)));
        }
        strip.show();
        delay(100);
    }
    clear();
}

void LedStrip::clear() {
    strip.clear();
    strip.show();
}

uint32_t LedStrip::getColor(uint8_t r, uint8_t g, uint8_t b) {
    return strip.Color(r, g, b);
} 