#include <Arduino.h>
#include "sequential_e.hpp"
#include "twinkle.hpp"
#include "solid_fill.hpp"
#include "color_fade_e.hpp"
#include "pulse_e.hpp"

// #define DEBUG
// #define BAUDRATE 9600

extern CRGB LED_STRIP[];

void setup() {
    // put your setup code here, to run once:
    #ifdef DEBUG
    Serial.begin(BAUDRATE);
    printf("sizeof char: %d\n", sizeof(char));
    printf("sizeof int: %d\n", sizeof(int));
    printf("sizeof uint: %d\n", sizeof(uint));
    printf("sizeof uint64: %d\n", sizeof(uint64_t));
    printf("sizeof long: %d\n", sizeof(long));
    printf("sizeof unsigned long: %d\n", sizeof(unsigned long));
    #endif
    randomSeed(analogRead(0));
    init_matrix();
    BaseSequential sqf(LED_STRIP, 32, CRGB(0, 0, 255), 20, 64, 5, 0, 1);
    BaseSequential sqf2(LED_STRIP + 32, 32, CRGB(120, 0, 0), 20, 64, 5, 31, -1);
    while(sqf.get_status() != DONE && sqf.get_status() != DONE){
        sqf.update();
        sqf2.update();
        FastLED.show();
        delay(1);
    }
}


void loop() {
    int num_effects = 3;
    BaseLightingEffect* effects[num_effects];
    int dir = 1;
    // ColorPulse* sqf_ptr = new ColorPulse(LED_STRIP, 64, CHSV(180, 255, 251), 20);
    SolidFill* sf_ptr = new SolidFill(LED_STRIP, 64, CRGB(0, 0, 0));
    effects[0] = sf_ptr;
    for (int i = 1; i < num_effects; i++){
        BaseSequential* sqf_ptr = new BaseSequential(LED_STRIP, 64, CRGB(100, 0, 255), 50, 255, 6, (63 * (i-1)), dir);
        effects[i] = sqf_ptr;
        dir *= -1;
    }

    #ifdef DEBUG
    printf("Beginning loop phase\n");
    printf(" Number of running effects: %d\n", num_effects);
    #endif

    while(1){
        for (int i = 1; i < num_effects; i++){
            effects[i]->update();

            if (effects[i]->get_status() == DONE){
                effects[i]->reset();
            }
        }
        FastLED.show();
        delay(1);
    }
}