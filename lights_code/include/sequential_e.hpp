#ifndef SEQUENTIAL_EFFECTS_HPP
#define SEQUENTIAL_EFFECTS_HPP

#include "lighting_defs.hpp"

class BaseSequential: public BaseAnimatedEffect{
public:
    BaseSequential(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint fade_amt, uint trail_size, uint start_pos=0, int8_t dir=1);

    virtual void reset();

protected:
    virtual void update_pos();

    CRGB color;
    uint fade_amt;
    uint trail_size;
    uint start_pos;
    uint pos;
    int8_t dir;     // 1 for increasing array, -1 for decreasing
};

class SequentialBounce: public BaseSequential{
public:
    SequentialBounce(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint fade_amt, uint trail_size, uint start_pos=0, int8_t start_dir=1);

    void reset();

protected:
    void update_pos();

    int8_t start_dir;   // keep track of set direction for resetting
};

// Sequential fade but the fade amt is random
class SequentialComet: public BaseSequential{
public:
    SequentialComet(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint fade_amt, uint trail_size, uint start_pos=0, int8_t dir=1);

    void update();
    void reset();
};

// class SequentialComet: public BaseLightingEffect{
// public:
//     SequentialComet(CRGB* data, uint nLeds, CRGB color, uint fade_amt, uint speed, uint start_pos=0, int8_t dir=1);

//     // void update();

// protected:
//     CRGB color;
//     uint fade_amt;
//     uint speed;
//     uint pos;
//     int8_t dir;
// };

#endif
