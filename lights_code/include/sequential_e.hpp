#ifndef SEQUENTIAL_EFFECTS_HPP
#define SEQUENTIAL_EFFECTS_HPP

#include "lighting_defs.hpp"

class BaseSequential: public AnimatedLightingEffect{
public:
    BaseSequential(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint fade_amt, uint trail_size, uint start_pos=0, int8_t dir=1);

    virtual void draw_frame();
    virtual void reset();

protected:
    virtual void update_status();
    virtual void update_frame();

    uint fade_amt;
    uint trail_size;
    uint start_pos;
    uint pos;
    int8_t dir;     // 1 for increasing array, -1 for decreasing
};

class SequentialBounce: public BaseSequential{
public:
    SequentialBounce(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint fade_amt, uint trail_size, uint start_pos=0, int8_t start_dir=1);
    void draw_frame();
    void reset();

protected:
    void update_status();
    void update_frame();

    int8_t start_dir;   // keep track of set direction for resetting
};

// Sequential fade but the fade amt is random
class SequentialComet: public BaseSequential{
public:
    SequentialComet(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint fade_amt, uint trail_size, uint start_pos=0, int8_t dir=1);

protected:
    void update_status();
    void update_frame();
};

#endif
