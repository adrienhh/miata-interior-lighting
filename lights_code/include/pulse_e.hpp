#ifndef PULSE_EFFECT_HPP
#define PULSE_EFFECT_HPP

#include "lighting_defs.hpp"

class ColorPulse: public BaseAnimatedEffect{
public:
    ColorPulse(CRGB* data, uint32_t nLeds, CHSV color, uint32_t delay):
        BaseAnimatedEffect(data, nLeds, delay),
        color(color),
        fade(0) {

    }

protected:
    void update_pos(){
        color.value = quadwave8(fade++);

        for (int i = 0; i < nLeds; i++){
            data[i] = color;
            millis();
        }
    }
    CHSV color;
    uint8_t fade;
};

#endif