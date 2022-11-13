#ifndef TWINKLE_HPP
#define TWINKLE_HPP

#include "lighting_defs.hpp"

class Twinkle: public BaseLightingEffect{
public:
    Twinkle(CRGB* data, uint nLeds, CRGB color, uint speed, uint max_particle_count, bool overlap=true);

    ~Twinkle();

    void update();

    void reset();

protected:
    CRGB color;
    uint speed;
    uint* pixel_array;              // array that keeps track of the position pixels were placed at
    uint particle_count;
    uint max_particle_count;
    bool overlap;
};

#endif
