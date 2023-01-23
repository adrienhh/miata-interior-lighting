#include "twinkle.hpp"

Twinkle::Twinkle(CRGB* data, uint nLeds, CRGB color, uint32_t delay, uint max_particle_count, bool overlap):
    BaseAnimatedEffect(data, nLeds, delay),
    color(color),
    particle_count(0),
    max_particle_count(max_particle_count),
    overlap(overlap) {
    pixel_array = new uint[max_particle_count];
}

Twinkle::~Twinkle(){
    delete[] pixel_array;
}

void Twinkle::update(){
    // status update
    if (status == DONE)
        return;
    if (particle_count >= max_particle_count){
        status = DONE;
        return;
    }
    if (status == READY)
        status = PLAYING;

    pixel_array[particle_count] = random(nLeds);
    particle_count++;
    for (int i = 0; i < particle_count; i++){
        data[pixel_array[i]] = color;
    }
}

void Twinkle::reset(){
    status = READY;
    particle_count = 0;     // will make the next update iteration clean up the LED array
}