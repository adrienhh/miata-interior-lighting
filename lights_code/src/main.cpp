#include <Arduino.h>
#include "lighting_effects.h"

void setup() {
    // put your setup code here, to run once:
    randomSeed(analogRead(0));
    init_matrix();
    converge_rgb(255, 0, 0, 5);
    FastLED.clear(true);
    diverge_rgb(100, 0, 150, 2);
    FastLED.clear(true);
    twinkle_random(20, 60);
    twinkle_rgb(100, 0, 150, 20, 60);
    solid_fill_rgb(100, 0, 150);
}


void loop() {
    // solid_fill_rgb(100, 0, 150);
}