#include <Arduino.h>
#include "lighting_effects.h"

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  init_matrix();

}


void loop() {
  // testing
  converge_rgb(100, 0, 150, 20);
  FastLED.clear(true);
  diverge_rgb(0, 0, 255, 20);
  FastLED.clear(true);
  twinkle_rgb(255, 0, 0, 20, 60);
  FastLED.clear(true);
  twinkle_random(20, 60);
  FastLED.clear(true);
}