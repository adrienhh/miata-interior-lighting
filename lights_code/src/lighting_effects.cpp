#include "lighting_effects.h"

#define NUM_RANDOM_COLORS 12


CRGB LED_STRIP[NUM_LEDS];

static const CRGB RANDOM_COLOR_SET[NUM_RANDOM_COLORS] = {
    CRGB::Red,
    CRGB::Blue,
    CRGB::Cyan,
    CRGB::Purple,
    CRGB::Fuchsia,
    CRGB::DarkViolet,
    CRGB::Orange,
    CRGB::MediumSpringGreen,
    CRGB::Wheat,
    CRGB::Navy,
    CRGB::Turquoise,
    CRGB::ForestGreen
};

void init_matrix(){
    pinMode(LED_PIN, OUTPUT);
    FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, NUM_LEDS);
    FastLED.setBrightness(16);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
}


void solid_fill_rgb(uint8_t r, uint8_t g, uint8_t b){
  for (int i = 0; i < NUM_LEDS; i++){
    LED_STRIP[i] = CRGB(100, 0, 150);
  }
  FastLED.show();
}

void blink_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate){
    for (int i = 0; i < NUM_LEDS; i++){
        LED_STRIP[i] = CRGB(r, g, b);
    }
    FastLED.show();
    delay(rate);
    
    FastLED.clear(true);
    delay(rate);
}

void converge_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate){
    for (int i = 0; i < CUSTOM_MIDPOINT; i++){
        LED_STRIP[i] = CRGB(r, g, b);
        LED_STRIP[NUM_LEDS-1-i] = CRGB(r, g, b);
        FastLED.show();
        delay(rate);
    }
}

void diverge_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate){
    int i = CUSTOM_MIDPOINT;
    int j = CUSTOM_MIDPOINT - 1;
    while (i >= 0 && j < NUM_LEDS){
        LED_STRIP[i] = CRGB(r, g, b);
        LED_STRIP[j] = CRGB(r, g, b);
        FastLED.show();
        i--;
        j++;
        delay(rate);
    }
}

void twinkle_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate, uint max){
    for (int i = 0; i < max; i++){
        LED_STRIP[random(NUM_LEDS)] = CRGB(r, g, b);
        FastLED.show();
        delay(rate);
    }
    FastLED.clear(true);
}

void twinkle_random(uint rate, uint max){
    for (int i = 0; i < max; i++){
        LED_STRIP[random(NUM_LEDS)] = RANDOM_COLOR_SET[random(NUM_RANDOM_COLORS)];
        FastLED.show();
        delay(rate);
    }
    FastLED.clear(true);
}
