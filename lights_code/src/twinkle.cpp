#include "twinkle.hpp"

Twinkle::Twinkle(CRGB* data, uint nLeds, CRGB color, uint32_t delay, uint max_particle_count, bool overlap):
    AnimatedLightingEffect(data, nLeds, color, delay),
    particle_count(0),
    max_particle_count(max_particle_count),
    overlap(overlap) {
    pixel_array = new uint[max_particle_count];
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
    pixel_array[particle_count] = random(nLeds);
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

// DONE