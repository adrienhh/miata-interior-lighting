#include "twinkle.hpp"

// Twinkle definitions
Twinkle::Twinkle(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint16_t max_particle_count, bool overlap):
    AnimatedLightingEffect(data, nLeds, color, delay),
    particle_count(0),
    max_particle_count(max_particle_count),
    overlap(overlap) {
    pixel_array = new int32_t[max_particle_count];
    memset(pixel_array, -1, max_particle_count * sizeof(int32_t));
}

Twinkle::~Twinkle(){
    delete[] pixel_array;
}

void Twinkle::update_status(){
    if (status == DONE){
        return;
    }
    else if (particle_count >= max_particle_count){
        status = DONE;
    }
    else if (status == READY){
        status = PLAYING;
    }
}

void Twinkle::update_frame(){
    uint32_t next_pixel = random(nLeds);
    if (overlap || (!overlap && pixel_array[particle_count] != -1)){
        pixel_array[particle_count] = random(nLeds);
    }
    particle_count++;
}

void Twinkle::draw_frame(){
    for (uint16_t i = 0; i < particle_count; i++){
        data[pixel_array[i]] = color;
    }
}

void Twinkle::reset(){
    status = READY;
    particle_count = 0;     // will make the next update iteration clean up the LED array
}

// TwinkleFade definitions TODO
TwinkleFade::TwinkleFade(CRGB* data, uint32_t nLeds, CRGB color, uint32_t delay, uint32_t fade_amt, bool overlap):
    AnimatedLightingEffect(data, nLeds, color, delay),
    particle_count(0),
    overlap(0){
    pixel_array = new int32_t[nLeds];   // TODO: complete
}


TwinkleFade::~TwinkleFade(){

}

// DONE