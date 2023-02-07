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

void AnimatedLightingEffect::update_after_delay(uint32_t cur_time){
    if (update_ready(cur_time)){
        update_status();
        if (status != DONE){
            update_frame();
        }
    }
}

bool AnimatedLightingEffect::update_ready(uint32_t cur_time){
    if (cur_time - last_update > delay){
        last_update = cur_time;
        return true;
    }
    else {
        return false;
    }
}

EffectStatus AnimatedLightingEffect::get_status(){
    return status;
}

void AnimatedLightingEffect::printCRGB(CRGB c){
    printf("CRGB(%d, %d, %d)\n", c.r, c.g, c.b);
}

void init_matrix(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, NUM_LEDS);
    FastLED.setBrightness(128);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 800);
    FastLED.clear();
}
