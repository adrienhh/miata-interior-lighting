#ifndef SEQUENTIAL_EFFECTS_H
#define SEQUENTIAL_EFFECTS_H

#include "lighting_defs.hpp"

class BaseSequential: public BaseLightingEffect{
public:
    BaseSequential(CRGB* data, uint nLeds, CRGB color, uint speed, uint fade_amt, uint trail_size, uint start_pos=0, int8_t dir=1);

    virtual void update();

    virtual void reset();

protected:
    CRGB color;
    uint speed;
    uint fade_amt;
    uint trail_size;
    uint start_pos;
    int8_t start_dir;
    uint pos;
    int8_t dir;     // 1 for increasing array, -1 for decreasing
};

// Gradually fills the array with a color
class SequentialFill: public BaseLightingEffect {
public:
    SequentialFill(CRGB* data, uint nLeds, CRGB color, uint speed, int8_t dir=1);

    void update();

protected:
    CRGB color;
    uint trail_size;
    uint speed;
    uint pos;
    int8_t dir;     // 1 for increasing array, -1 for decreasing
};

// Same as class above but the color will fade away as the array fills up
class SequentialFade: public BaseLightingEffect {
public:
    SequentialFade(CRGB* data, uint nLeds, CRGB color, uint fade_amt, uint speed, uint start_pos=0, int8_t dir=1);

    void update();

protected:
    CRGB color;
    uint fade_amt;
    uint speed;
    uint pos;
    int8_t dir;
};

class SequentialComet: public BaseLightingEffect{
public:
    SequentialComet(CRGB* data, uint nLeds, CRGB color, uint fade_amt, uint speed, uint start_pos=0, int8_t dir=1);

    // void update();

protected:
    CRGB color;
    uint fade_amt;
    uint speed;
    uint pos;
    int8_t dir;
};

#endif
