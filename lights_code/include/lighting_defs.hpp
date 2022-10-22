#ifndef LIGHTING_DEFINITIONS_H
#define LIGHTING_DEFINITIONS_H

#include <FastLED.h>

#define LED_PIN 13
#define NUM_LEDS 64

#define CHIP_SET WS2812B
#define COLOR_CODE GRB

// Abstract Base class for all lighting effects
class BaseLightingEffect {
public:
    BaseLightingEffect(CRGB* data, uint nLeds): data(data), 
        nLeds(nLeds){
    }

    // calculates the next frame of the effect. DOES NOT UPDATE DISPLAY
    virtual void update(){

    }

protected:
    CRGB* data;         // section of array this effect will be using
    uint nLeds;         // number of LEDs of the array above
};

void init_matrix();

#endif