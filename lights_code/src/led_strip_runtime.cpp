#include "led_strip_runtime.hpp"

extern CRGB LED_STRIP[];

AnimatedLightingEffect* effects[NUM_EFFECTS];

void thread_init_effects(void* _){

}

void thread_update_strip(void* _){
    #ifdef DEBUG
    printf("In thread_update_strip\n");
    #endif
    while(true){
        // maybe mutex logic here
        for (int i = 0; i < NUM_EFFECTS; i++){
            effects[i]->draw_frame();
        }
        #ifdef DEBUG
        printf("About to draw frame\n");
        #endif
        FastLED.show();
        vTaskDelay(32);
    }
}

void thread_update_animations(void* _){
    #ifdef DEBUG
    printf("Beginning thread_update_animation\n");
    printf(" Number of running effects: %d\n", NUM_EFFECTS);
    #endif

    while(1){
        for (int i = 1; i < NUM_EFFECTS; i++){
            effects[i]->update_after_delay();

            if (effects[i]->get_status() == DONE){
                effects[i]->reset();
            }
        }
        vTaskDelay(10);
    }
}
