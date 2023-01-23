#include "lighting_defs.hpp"

CRGB LED_STRIP[NUM_LEDS];

// BaseLightingEffect method definitions
BaseLightingEffect::BaseLightingEffect(CRGB* data, uint nLeds):
    data(data), 
    nLeds(nLeds),
    status(READY) {
}

EffectStatus BaseLightingEffect::get_status(){
    #ifdef DEBUG
    // printf("get_status() -> %d\n", status);
    #endif
    return status;
}

// BaseAnimatedEffects method definitions
BaseAnimatedEffect::BaseAnimatedEffect(CRGB* data, uint32_t nLeds, uint32_t delay):
    BaseLightingEffect(data, nLeds),
    delay(delay),
    last_update(0){
}

inline void BaseAnimatedEffect::update(){
    if (update_ready()){
        update_pos();
    }
}

bool BaseAnimatedEffect::update_ready(){
    uint32_t cur_time = millis();

    if (cur_time - last_update > delay){
        #ifdef DEBUG
        printf("Updating frame. last_update: %d, cur_time %d\n", last_update, cur_time);
        #endif
        last_update = cur_time;
        return true;
    }
    else {
        #ifdef DEBUG
        printf("No update. Time elapsed: %d ms\n", cur_time - last_update);
        #endif
        return false;
    }
}

void init_matrix(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, NUM_LEDS);
    FastLED.setBrightness(16);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
}
