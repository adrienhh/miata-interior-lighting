#ifndef SOLID_FILL_H
#define SOLID_FILL_H

#include "lighting_defs.hpp"

class SolidFill: public AnimatedLightingEffect{
public:
    SolidFill(CRGB* data, uint32_t nLeds, CRGB color):
        AnimatedLightingEffect(data, nLeds, color, 0) {

    }

    void update_after_delay(){
        // overrided to do nothing, saves performance ig
    }

    void update_status(){
        if (status == READY){
            status = PLAYING;
        }
    }

    void draw_frame(){
        for (int i = 0; i < nLeds; i++){
            this->data[i] = this->color;
        }
    }

    void update_frame(){

    }

    void reset(){

    }
};

#endif

// DONE