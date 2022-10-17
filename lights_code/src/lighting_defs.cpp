#include "lighting_defs.hpp"

CRGB LED_STRIP[NUM_LEDS];

void init_matrix(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, NUM_LEDS);
    FastLED.setBrightness(16);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
}