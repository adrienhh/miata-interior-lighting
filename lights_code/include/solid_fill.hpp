#ifndef SOLID_FILL_H
#define SOLID_FILL_H

#include "lighting_defs.hpp"

class SolidFill: public BaseLightingEffect{
public:
    SolidFill(CRGB* data, uint nLeds, CRGB color): BaseLightingEffect(data, nLeds), 
        color(color) {

    }

    void update(){
        for (int i = 0; i < nLeds; i++){
            this->data[i] = this->color;
        }
    }
protected:
    CRGB color;
};

#endif