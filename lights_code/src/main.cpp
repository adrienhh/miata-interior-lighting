#include <Arduino.h>
#include "freertos/task.h"
#include "led_strip_runtime.hpp"

// #define DEBUG
// #define BAUDRATE 9600

extern CRGB LED_STRIP[];
extern AnimatedLightingEffect* effects[];

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

    // int num_effects = 4;
    // BaseLightingEffect* effects[num_effects];
    int dir = 1;
    // ColorPulse* sqf_ptr = new ColorPulse(LED_STRIP, 64, CHSV(180, 255, 251), 20);
    SolidFill* sf_ptr = new SolidFill(LED_STRIP, 64, CRGB(0, 0, 0));
    effects[0] = sf_ptr;
    for (int i = 1; i < NUM_EFFECTS; i++){
        if (i > 1){
            BaseSequential* sqf_ptr = new BaseSequential(LED_STRIP, 64, CRGB(100, 0, 255), 64, 64, 5, (63 * (i-2)), dir);
            effects[i] = sqf_ptr;
            dir *= -1;
        }
        else{
            Twinkle* t_ptr = new Twinkle(LED_STRIP, 64, CRGB(0, 50, 0), 500, 16);
            effects[i] = t_ptr;
        }
    }

    TaskHandle_t led_updater_handle = NULL;
    TaskHandle_t animation_updater_handle = NULL;

    #ifdef DEBUG
    printf("Initializing threads.\n");
    #endif

    xTaskCreate(thread_update_strip, "LED update", 1024, NULL, tskIDLE_PRIORITY, &led_updater_handle);
    xTaskCreate(thread_update_animations, "Animation update", 2048, NULL, tskIDLE_PRIORITY, &animation_updater_handle);
}


void loop() {

}