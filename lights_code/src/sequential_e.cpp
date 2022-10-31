#include "sequential_e.hpp"

// BaseSequential definitions
BaseSequential::BaseSequential(CRGB* data, uint nLeds, CRGB color, uint speed, uint fade_amt, uint trail_size, uint start_pos, int8_t start_dir):
    BaseLightingEffect(data, nLeds),
    color(color),
    speed(speed),
    fade_amt(fade_amt),
    trail_size(trail_size),
    start_pos(start_pos),
    start_dir(start_dir),
    pos(start_pos),
    dir(start_dir) {
}

void BaseSequential::update(){
    // update status
    if (status == DONE)
        return;
    if ( pos >= nLeds || pos < 0){     // either when the object was set incorrectly or effect is done playing
        status = DONE;
        return;
    }
    if (status == READY)
        status = PLAYING;

    int count = 0;
    CRGB temp_color = color;
    for (int i = pos; count <= trail_size && i >= 0 && i < nLeds; i -= dir){
        data[i] = temp_color.fadeToBlackBy(fade_amt);
        count++;
    }
    data[pos] = color;
    pos += dir;
}

void BaseSequential::reset(){
    status = READY;
    dir = start_dir;
    pos = start_pos;
}

// SequentialComet definitions
SequentialComet::SequentialComet(CRGB* data, uint nLeds, CRGB color, uint fade_amt, uint speed, uint start_pos, int8_t dir): 
    BaseLightingEffect(data, nLeds),
    color(color),
    fade_amt(fade_amt),
    speed(speed),
    pos(start_pos),
    dir(dir){

}
