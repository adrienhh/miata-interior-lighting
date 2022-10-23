#include <Arduino.h>
#include "sequential_e.hpp"
#include "solid_fill.hpp"

// #define DEBUG
// #define BAUDRATE 9600

extern CRGB LED_STRIP[];

void setup() {
    // put your setup code here, to run once:
    #ifdef DEBUG
    Serial.begin(BAUDRATE);
    #endif
    randomSeed(analogRead(0));
    init_matrix();

    BaseSequential sqf(LED_STRIP, 150, CRGB(0, 0, 255), 20, 64, 5, 0, 1);
    BaseSequential sqf2(LED_STRIP + 150, 150, CRGB(120, 0, 0), 20, 64, 5, 149, -1);
    for (int i = 0; i < NUM_LEDS; i++){
        sqf.update();
        sqf2.update();
        FastLED.show();
        delay(10);
    }
}


void loop() {
    int num_effects = 2;
    BaseLightingEffect* effects[num_effects];
    int dir = 1;
    // SolidFill* sqf_ptr = new SolidFill(LED_STRIP, 300, CRGB(32, 0, 64));
    // effects[0] = sqf_ptr;
    for (int i = 0; i < num_effects; i++){
        BaseSequential* sqf_ptr = new BaseSequential(LED_STRIP + i * 150, 150, CRGB(160, 0, 255), 20, 64, 6, i * 149, dir);
        effects[i] = sqf_ptr;
        dir *= -1;
    }

    while(1){
        // sqf.update();
        for (int i = 0; i < num_effects; i++){
            effects[i]->update();
            FastLED.show();

            if (effects[i]->get_status() == DONE){
                effects[i]->reset();
            }
        }
        FastLED.show();
        delay(75);  // did not implement rate yet
    }
}