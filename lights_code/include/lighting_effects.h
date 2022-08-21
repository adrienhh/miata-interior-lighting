#ifndef LIGHTING_EFFECTS_H
#define LIGHTING_EFFECTS_H

#include <FastLED.h>

#define LED_PIN 13
#define NUM_LEDS 300

#define CHIP_SET WS2812B
#define COLOR_CODE GRB

#define CUSTOM_MIDPOINT 150

void init_matrix();

void solid_fill_rgb(uint8_t r, uint8_t g, uint8_t b);
void blink_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate);
void converge_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate);
void diverge_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate);
void twinkle_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate, uint max);

void twinkle_random(uint rate, uint max);



#endif
