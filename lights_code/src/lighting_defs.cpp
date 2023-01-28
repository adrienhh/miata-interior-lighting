#include "lighting_defs.hpp"

CRGB LED_STRIP[NUM_LEDS];

// AnimatedLightingEffect method definitions
AnimatedLightingEffect::AnimatedLightingEffect(CRGB* data, uint nLeds, CRGB color, uint32_t delay):
    data(data), 
    nLeds(nLeds),
    color(color),
    delay(delay),
    last_update(0),
    status(READY) {
}

void AnimatedLightingEffect::update_after_delay(){
    if (update_ready()){
        update_status();
        if (status != DONE){
            update_frame();
        }
    }
}

bool AnimatedLightingEffect::update_ready(){
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

EffectStatus AnimatedLightingEffect::get_status(){
    #ifdef DEBUG
    // printf("get_status() -> %d\n", status);
    #endif
    return status;
}

void init_matrix(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, NUM_LEDS);
    FastLED.setBrightness(16);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
}
