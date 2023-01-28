#include "color_fade_e.hpp"

// RainbowFade definitions
RainbowFade::RainbowFade(CRGB* data, uint32_t nLeds, CHSV start_color, uint32_t delay):
    AnimatedLightingEffect(data, nLeds, start_color, delay),
    start_color(start_color),
    color(start_color){

}

void RainbowFade::reset(){
    color = start_color;
    status = READY;
}

void RainbowFade::update_status(){
    if (status == READY){
        return;
    }
}

void RainbowFade::update_frame(){
    color.hue += 1;
}

void RainbowFade::draw_frame(){
    for (uint16_t i = 0; i < nLeds; i++){
        data[i] = color;
    }
}