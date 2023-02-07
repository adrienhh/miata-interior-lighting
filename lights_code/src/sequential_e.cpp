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
    #ifdef DEBUG
    CRGB temp_color = color;
    uint16_t count = 0;
    for (uint16_t i = pos; count < trail_size && i >= 0 && i < nLeds; i -= dir){
        printf("pixel %d = ", i);
        printCRGB(temp_color);
        temp_color.fadeToBlackBy(fade_amt);
        count++;
    }
    #endif
    pos += dir;
}

void BaseSequential::draw_frame(){
    uint16_t count = 0;
    CRGB temp_color = color;
    for (uint16_t i = pos; count < trail_size && i >= 0 && i < nLeds; i -= dir){
        data[i] = temp_color;
        temp_color.fadeToBlackBy(fade_amt);
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
        data[i] = temp_color;
        temp_color.fadeToBlackBy(fade_amt);
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
SequentialComet::SequentialComet(CRGB* data, uint nLeds, CRGB color, uint32_t delay, uint8_t fade_amt, uint trail_size, uint start_pos, int8_t dir, uint8_t fade_rate):
    BaseSequential(data, nLeds, color, delay, fade_amt, trail_size, start_pos, dir),
    fade_rate(fade_rate)
    //trail_color_queue(CircularQueue(trail_size)){
    {
}

SequentialComet::~SequentialComet(){

}

void SequentialComet::draw_frame(){
    if (dir == 1){
        for (int i = pos - (trail_color_queue.size() * dir); i < pos; i++){
            draw_trail(i);
        }
    } 
    else{
        for (int i = pos + trail_color_queue.size(); i > pos; i--){
            draw_trail(i);
        }
    }
}

void SequentialComet::draw_trail(uint32_t index){
    // CHSV temp_color = rgb2hsv_approximate(color);
    CRGB temp_color = trail_color_queue.front();
    trail_color_queue.pop();

    // temp_color.value = 255 - fade_val;

    data[index] = temp_color;
    
    trail_color_queue.push(temp_color);
}

void SequentialComet::update_frame(){
    #ifdef DEBUG
    uint16_t temp_len = trail_color_queue.size();
    for (int i = 0; i < temp_len; i++){
        CRGB temp_color = trail_color_queue.front();
        trail_color_queue.pop();
        printf("trail_color_queue[%d] = ", i);
        printCRGB(temp_color);
        trail_color_queue.push(temp_color);
    }
    #endif
    pos += dir;
    uint16_t qlen = trail_color_queue.size();
    for (int i = 0; i < qlen; i++){
        CRGB temp_color = trail_color_queue.front();
        trail_color_queue.pop();
        if (random(fade_rate) != 0){
            temp_color = temp_color.fadeToBlackBy(fade_amt);
        }
        if (qlen != trail_size || i != 0){
            trail_color_queue.push(temp_color);
        }
    }

    trail_color_queue.push(color);
}

void SequentialComet::reset(){
    status = READY;
    pos = start_pos;
    while (trail_color_queue.empty() != true){
        trail_color_queue.pop();
    }
}

// DONE
