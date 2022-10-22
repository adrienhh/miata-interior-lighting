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
    //SolidFill startEffect(LED_STRIP, NUM_LEDS, CRGB(120, 0, 255));
    //startEffect.update();
    //FastLED.show();
    //delay(500);
    //FastLED.clear();
    SequentialFill sqf(LED_STRIP, 64, CRGB(0, 0, 255), 20);
    SequentialFill sqf2(LED_STRIP, 64, CRGB(120, 0, 0), 20, -1);
    for (int i = 0; i < NUM_LEDS; i++){
        sqf.update();
        sqf2.update();
        FastLED.show();
        delay(50);
    }
}


void loop() {
    int num_effects = 3;
    BaseLightingEffect* effects[num_effects];
    int dir = 1;
    SolidFill* sqf_ptr = new SolidFill(LED_STRIP, 64, CRGB(0, 0, 0));
    effects[0] = sqf_ptr;
    for (int i = 1; i < num_effects; i++){
        BaseSequential* sqf_ptr = new BaseSequential(LED_STRIP, 64, CRGB(100, 0, 255), 20, 64, 4, (i-1) * 63, dir);
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
        delay(100);  // did not implement rate yet
    }
}