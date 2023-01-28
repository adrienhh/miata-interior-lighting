#ifndef PULSE_EFFECT_HPP
#define PULSE_EFFECT_HPP

#include "lighting_defs.hpp"

class ColorPulse: public AnimatedLightingEffect{
public:
    ColorPulse(CRGB* data, uint32_t nLeds, CHSV color, uint32_t delay):
        AnimatedLightingEffect(data, nLeds, color, delay),
        color(color),
        fade(0) {

    }

    void draw_frame(){
        for (int i = 0; i < nLeds; i++){
            data[i] = color;
        }
    }

protected:
    void update_status(){
        if (status == READY){
            status = PLAYING;
        }
    }

    void update_frame(){
        color.value = quadwave8(fade++);
    }
    CHSV color;
    uint8_t fade;
};

#endif