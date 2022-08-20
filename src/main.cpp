#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 13
#define LED_STRIP_LEN 300

#define CHIP_SET WS2812B
#define COLOR_CODE GRB

#define MIDPOINT 150

CRGB LED_STRIP[LED_STRIP_LEN];

void sequential_fill_half(char r, char g, char b){
  for (int i = 0; i < MIDPOINT; i++){
    LED_STRIP[i] = CRGB(r, g, b);
    LED_STRIP[LED_STRIP_LEN-1-i] = CRGB(r, g, b);
    FastLED.show();
  }
}

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<CHIP_SET, LED_PIN, COLOR_CODE>(LED_STRIP, LED_STRIP_LEN);
  randomSeed(analogRead(0));
  FastLED.setBrightness(50);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();

  sequential_fill_half(100, 0, 150);
}

void le_blink(char r, char g, char b, uint rate){
  for (int i = 0; i < LED_STRIP_LEN; i++){
    LED_STRIP[i] = CRGB(r, g, b);
  }
  FastLED.show();
  delay(rate);
  
  FastLED.clear();
  FastLED.show();
  delay(rate);
}

void loop() {
  for (int i = 0; i < LED_STRIP_LEN; i++){
    LED_STRIP[i] = CRGB(100, 0, 150);
  }
  FastLED.show();
}