#include <Arduino.h>
#include "freertos/task.h"
#include "led_strip_runtime.hpp"

#define DEBUG
#define BAUDRATE 9600

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

    TaskHandle_t animation_updater_handle = NULL;

    #ifdef DEBUG
    printf("Initializing threads.\n");
    #endif

    xTaskCreate(thread_process_animations, "Animation update", 2048, NULL, tskIDLE_PRIORITY, &animation_updater_handle);
}


void loop() {

}