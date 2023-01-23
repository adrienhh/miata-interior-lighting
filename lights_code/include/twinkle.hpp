#ifndef TWINKLE_HPP
#define TWINKLE_HPP

#include "lighting_defs.hpp"

class Twinkle: public BaseAnimatedEffect{
public:
    Twinkle(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint max_particle_count, bool overlap=true);

    ~Twinkle();

    void update();

    void reset();

protected:
    CRGB color;
    uint* pixel_array;              // array that keeps track of the position pixels were placed at
    uint particle_count;
    uint max_particle_count;
    bool overlap;
};

#endif
