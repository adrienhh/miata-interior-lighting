#include "sequential_e.hpp"

// BaseSequential definitions
BaseSequential::BaseSequential(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint8_t fade_amt, uint trail_size, uint start_pos, int8_t dir):
    AnimatedLightingEffect(data, nLeds, color, delay),
    fade_amt(fade_amt),
    trail_size(trail_size),
    start_pos(start_pos),
    pos(start_pos),
    dir(dir) {
}

void BaseSequential::update_status(){
    if (status == DONE){
        return;
    }
    else if (pos >= nLeds || pos < 0){     // either when the object was set incorrectly or effect is done playing
        // TODO: need to update the last items in the array
        status = DONE;
    }
    else if (status == READY){
        status = PLAYING;
    }
}

void BaseSequential::update_frame(){
    pos += dir;
}

void BaseSequential::draw_frame(){
    uint16_t count = 0;
    CRGB temp_color = color;
    for (uint16_t i = pos; count < trail_size && i >= 0 && i < nLeds; i -= dir){
        data[i] = temp_color.fadeToBlackBy(fade_amt);
        count ++;
    }
    data[pos] = color;
}

void BaseSequential::reset(){
    status = READY;
    pos = start_pos;
}

// SequentialBounce definitions
SequentialBounce::SequentialBounce(CRGB* data, uint nLeds, CRGB color, uint speed, uint8_t fade_amt, uint trail_size, uint start_pos, int8_t start_dir):
    BaseSequential(data, nLeds, color, speed, fade_amt, trail_size, start_pos, start_dir),
    start_dir(start_dir){      // start_dir in parent class call refers to general direction of base sequential effect

}

void SequentialBounce::update_status(){
    if (status == READY){
        status = PLAYING;
    }
}

void SequentialBounce::update_frame(){
    // Swap directions if pos will go out of bound. Unlike parent effect this will never be done playing
    if (pos >= nLeds || pos < 0){
        dir *= -1;
        pos += dir;
    }
    pos += dir;
}

void SequentialBounce::draw_frame(){
    uint16_t count = 0;
    CRGB temp_color = color;
    for (int i = pos; count <= trail_size && i >= 0 && i < nLeds; i -= dir){
        data[i] = temp_color.fadeToBlackBy(fade_amt);
        count++;
    }
    data[pos] = color;
}

void SequentialBounce::reset(){
    status = READY;
    dir = start_dir;
    pos = start_pos;
}


// TODO: SequentialComet definitions
SequentialComet::SequentialComet(CRGB* data, uint nLeds, CRGB color, uint32_t delay, uint8_t fade_amt, uint trail_size, uint start_pos, int8_t dir):
    BaseSequential(data, nLeds, color, delay, fade_amt, trail_size, start_pos, dir)
    //trail_brightness_queue(CircularQueue(trail_size)){
    {
}

SequentialComet::~SequentialComet(){

}

void SequentialComet::draw_frame(){
    if (dir == 1){
        for (int i = pos - (trail_brightness_queue.size() * dir); i < pos; i++){
            draw_trail(i);
        }
    } 
    else{
        for (int i = pos + trail_brightness_queue.size(); i > pos; i--){
            draw_trail(i);
        }
    }
}

void SequentialComet::draw_trail(uint32_t index){
    CRGB temp_color = color;
    // CHSV temp_color = rgb2hsv_approximate(color);
    uint8_t fade_val = trail_brightness_queue.front();
    trail_brightness_queue.pop();

    // temp_color.value = 255 - fade_val;
    // data[index] = temp_color;
    data[index] = temp_color.fadeToBlackBy(fade_val);
    // data[index] = temp_color.nscale8(fade_val);
    
    trail_brightness_queue.push(fade_val);
}

void SequentialComet::update_frame(){
    #ifdef DEBUG
    uint16_t temp_len = trail_brightness_queue.size();
    for (int i = 0; i < temp_len; i++){
        uint16_t fade_val = trail_brightness_queue.front();
        trail_brightness_queue.pop();
        printf("trail_brightness_queue[%d] = %d\n", i, fade_val);
        trail_brightness_queue.push(fade_val);
    }
    #endif
    pos += dir;
    uint16_t qlen = trail_brightness_queue.size();
    for (int i = 0; i < qlen; i++){
        uint16_t fade_val = trail_brightness_queue.front();
        trail_brightness_queue.pop();
        if (random(2) == 1){
            fade_val += fade_amt;
            if (fade_val > 255){
                fade_val = 255;
            }
        }
        if (qlen != trail_size || i != 0){
            trail_brightness_queue.push(fade_val);
        }
    }

    trail_brightness_queue.push(0);
}

void SequentialComet::reset(){
    status = READY;
    pos = start_pos;
    while (trail_brightness_queue.empty() != true){
        trail_brightness_queue.pop();
    }
}

// DONE
