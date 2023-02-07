#ifndef TWINKLE_HPP
#define TWINKLE_HPP

#include "lighting_defs.hpp"

class Twinkle: public AnimatedLightingEffect{
public:
    Twinkle(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint16_t max_particle_count, bool overlap=true);
    ~Twinkle();

    void draw_frame();
    void reset();

protected:
    void update_status();
    void update_frame();

    int32_t* pixel_array;              // array that keeps track of the position pixels were placed at
    uint16_t particle_count;
    uint16_t max_particle_count;
    bool overlap;
};

class TwinkleFade: public AnimatedLightingEffect{
public:
    TwinkleFade(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint32_t fade_amt, bool overlap=true);
    ~TwinkleFade();

    void draw_frame();
    void reset();

protected:
    int32_t* pixel_array;
    uint16_t particle_count;
    bool overlap;
};

#endif
