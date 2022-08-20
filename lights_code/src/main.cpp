#include <Arduino.h>
#include "lighting_effects.h"

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  init_matrix();

  converge_rgb(100, 0, 150, 20);
}


void loop() {

}