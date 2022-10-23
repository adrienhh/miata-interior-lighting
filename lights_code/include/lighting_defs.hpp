#ifndef LIGHTING_DEFINITIONS_H
#define LIGHTING_DEFINITIONS_H

#include <FastLED.h>

#define LED_PIN 13
#define NUM_LEDS 300

#define CHIP_SET WS2812B
#define COLOR_CODE GRB

enum EffectStatus{
    READY,
    PLAYING,
    PAUSED,
    DONE
};

// Abstract Base class for all lighting effects
class BaseLightingEffect {
public:
    BaseLightingEffect(CRGB* data, uint nLeds);

    // calculates the next frame of the effect. DOES NOT UPDATE DISPLAY
    virtual void update(){

    }

    // Allows us to replay an effect by resetting it
    virtual void reset(){

    }

    EffectStatus get_status();

protected:
    CRGB* data;             // section of array this effect will be using
    uint nLeds;             // number of LEDs of the array above
    EffectStatus status;    // status of current lighting effect
};

void init_matrix();

#endif