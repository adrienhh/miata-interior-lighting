#include <Arduino.h>
#include "sequential_e.hpp"
#include "solid_fill.hpp"

extern CRGB LED_STRIP[];

void setup() {
    // put your setup code here, to run once:
    randomSeed(analogRead(0));
    init_matrix();
    SolidFill startEffect(LED_STRIP, NUM_LEDS, CRGB(120, 0, 255));
    startEffect.update();
    FastLED.show();
    delay(500);
}


void loop() {
    SequentialFill sqf(LED_STRIP, 8, CRGB(120, 0, 255), 20);

    while(1){
        sqf.update();
        FastLED.show();
        delay(50);  // did not implement rate yet
        FastLED.clear();
    }
}