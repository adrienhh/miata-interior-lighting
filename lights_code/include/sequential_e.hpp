#ifndef SEQUENTIAL_EFFECTS_H
#define SEQUENTIAL_EFFECTS_H

#include "lighting_defs.hpp"

// Gradually fills the array with a color
class SequentialFill: public BaseLightingEffect {
public:
    SequentialFill(CRGB* data, uint nLeds, CRGB color, uint rate, int8_t dir=1): BaseLightingEffect(data, nLeds),
        color(color),
        rate(rate),
        dir(dir) {
        if (dir == 1)
            this->pos = 0;
        else if (dir == -1)
            this->pos = this->nLeds - 1;
        else
            // invalid value
            raise;
    }

    void update(){
        if (this->pos >= this->nLeds || this->pos < 0){
            this->dir *= -1;
            this->pos += this->dir;
        }
        this->data[this->pos] = this->color;
        this->pos += dir;
    }

protected:
    CRGB color;
    uint rate;
    uint pos;
    int8_t dir;     // 1 for increasing array, -1 for decreasing
};

// Same as class above but the color will fade away as the array fills up
class SequentialFade: public BaseLightingEffect {
public:
    SequentialFade(CRGB* data, uint nLeds, CRGB color, uint rate, int8_t dir=1): BaseLightingEffect(data, nLeds),
        color(color),
        rate(rate),
        dir(dir) {
        if (dir == 1)
            this->pos = 0;  // as we will increment this variable
        else if (dir == -1)
            this->pos = this->nLeds - 1;
        else
            // invalid value
            raise;

    }

    // bool update();       // no def atm

protected:
    CRGB color;
    uint rate;
    uint pos;
    int8_t dir;
};

#endif
