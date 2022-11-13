#ifndef TWINKLE_HPP
#define TWINKLE_HPP

#include "lighting_defs.hpp"

class Twinkle: public BaseLightingEffect{
public:
    Twinkle(CRGB* data, uint nLeds, CRGB color, uint speed, uint max_particle_count, bool overlap=true):
        BaseLightingEffect(data, nLeds),
        color(color),
        speed(speed),
        particle_count(0),
        max_particle_count(max_particle_count),
        overlap(overlap) {

    }

    void update(){
        // status update
        if (status == DONE)
            return;
        if (particle_count >= max_particle_count){
            status = DONE;
            return;
        }
        if (status == READY)
            status = PLAYING;

        data[random(nLeds)] = color;
        particle_count++;
    }

    void reset(){
        status = READY;
        particle_count = 0;
        // TODO: erase the previously placed particles
    }

protected:
    CRGB color;
    uint speed;
    uint particle_count;
    uint max_particle_count;
    bool overlap;
};

#endif
