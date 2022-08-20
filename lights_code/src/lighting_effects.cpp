#include "lighting_effects.h"

CRGB LED_STRIP[LED_STRIP_LEN];

void init_matrix(){
    FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, LED_STRIP_LEN);
    FastLED.setBrightness(50);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.clear();
}


void fill_rgb(uint8_t r, uint8_t g, uint8_t b){
  for (int i = 0; i < LED_STRIP_LEN; i++){
    LED_STRIP[i] = CRGB(100, 0, 150);
  }
  FastLED.show();
}

void blink_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate){
    for (int i = 0; i < LED_STRIP_LEN; i++){
        LED_STRIP[i] = CRGB(r, g, b);
    }
    FastLED.show();
    delay(rate);
    
    FastLED.clear();
    FastLED.show();
    delay(rate);
}

void converge_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate){
    for (int i = 0; i < MIDPOINT; i++){
        LED_STRIP[i] = CRGB(r, g, b);
        LED_STRIP[LED_STRIP_LEN-1-i] = CRGB(r, g, b);
        delay(rate);
        FastLED.show();
    }
}

void diverge_rgb(uint8_t r, uint8_t g, uint8_t b, uint rate){

}
