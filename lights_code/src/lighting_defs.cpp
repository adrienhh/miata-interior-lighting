#include "lighting_defs.hpp"

CRGB LED_STRIP[NUM_LEDS];

BaseLightingEffect::BaseLightingEffect(CRGB* data, uint nLeds): data(data), 
    nLeds(nLeds),
    status(READY) {
}

EffectStatus BaseLightingEffect::get_status(){
    return status;
}

void init_matrix(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, NUM_LEDS);
    FastLED.setBrightness(16);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
}