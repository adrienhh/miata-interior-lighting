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


// SequentialFill definitions
SequentialFill::SequentialFill(CRGB* data, uint nLeds, CRGB color, uint speed, int8_t dir): 
    BaseLightingEffect(data, nLeds),
    color(color),
    speed(speed),
    dir(dir) {
    if (dir == 1)
        pos = 0;
    else if (dir == -1)
        pos = nLeds - 1;
    else
        // invalid value
        raise;
}

void SequentialFill::update(){
    if (pos >= nLeds || pos < 0){
        dir *= -1;
        pos += dir;
    }
    data[pos] = color;
    pos += dir;
}

// SequentialFade definitions
SequentialFade::SequentialFade(CRGB* data, uint nLeds, CRGB color, uint fade_amt, uint speed, uint start_pos, int8_t dir): 
    BaseLightingEffect(data, nLeds),
    color(color),
    fade_amt(fade_amt),
    speed(speed),
    pos(start_pos),
    dir(dir) {

}

void SequentialFade::update(){
    if (pos >= nLeds || pos < 0){
        dir *= -1;
        pos += dir;
    }
    CRGB temp_color = color;
    uint count = 0;
    if (dir == 1){
        while ((temp_color.r > 0 || temp_color.g > 0 || temp_color.b > 0) && pos - count >= 0){
            data[pos - count] = temp_color;
            temp_color /= 2;
            count++;
        }
    }
    else {
        while ((temp_color.r > 0 || temp_color.g > 0 || temp_color.b > 0) && pos + count <= nLeds){
            data[pos + count] = temp_color;
            temp_color /= 2;
            count++;
        }
    }
    pos += dir;
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
