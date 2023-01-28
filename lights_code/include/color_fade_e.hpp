#ifndef COLOR_FADE_EFFECTS_HPP
#define COLOR_FADE_EFFECTS_HPP

#include "lighting_defs.hpp"

class RainbowFade: public AnimatedLightingEffect{
public:
    RainbowFade(CRGB* data, uint32_t nLeds, CHSV start_color, uint32_t delay);

    void draw_frame();
    void reset();

protected:
    void update_status();
    void update_frame();

    CHSV start_color;
    CHSV color;
};

// Two color fade, then implement n color fade
// class ColorFade: public BaseAnimatedEffect{
// public:
//     ColorFade(CRGB* data, uint32_t nLeds, CHSV start_color, CHSV end_color, uint32_t delay):
//         BaseAnimatedEffect(data, nLeds, delay),
//         start_color(start_color),
//         end_color(end_color){

//     }

//     void reset() {
//         cur_color = start_color;
//         status = READY;
//     }
// protected:
//     CHSV cur_color;
//     CHSV start_color;
//     CHSV end_color;
// };


#endif
