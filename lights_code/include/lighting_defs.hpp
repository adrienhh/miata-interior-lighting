#ifndef LIGHTING_DEFINITIONS_H
#define LIGHTING_DEFINITIONS_H

#include <FastLED.h>

#define LED_PIN 13
#define NUM_LEDS 64

#define CHIP_SET WS2812B
#define COLOR_CODE GRB

enum EffectStatus{
    READY,
    PLAYING,
    PAUSED,
    DONE
};

// Abstract Base class for all lighting effects
class AnimatedLightingEffect {
public:
    AnimatedLightingEffect(CRGB* data, uint nLeds, CRGB color, uint32_t delay);

    // calls update() if and only if delay (ms) has spanned since last call
    void update_after_delay(uint32_t cur_time);

    // pushes the current state of the animation (object) to the data array
    virtual void draw_frame() = 0;

    // Allows us to replay an effect by resetting it
    virtual void reset() = 0;

    EffectStatus get_status();

protected:
    struct PixelVal{
        uint32_t pos;
        CRGB val;
    };

    // updated the animation by a frame. DOES NOT UPDATE DISPLAY
    virtual void update_frame() = 0;

    virtual void update_status() = 0;

    bool update_ready(uint32_t cur_time);

    void printCRGB(CRGB c);

    // data members
    CRGB* data;             // section of array this effect will be using
    uint32_t nLeds;         // number of LEDs of the array above
    CRGB color;             // RGB representation of the saved color
    EffectStatus status;    // status of current lighting effect
    uint32_t last_update;   // number to represent last time the frame was updated
    uint32_t delay;         // set delay between frames in the animation
};

void init_matrix();

#endif