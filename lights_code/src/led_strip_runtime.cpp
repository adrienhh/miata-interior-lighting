#include "led_strip_runtime.hpp"

extern CRGB LED_STRIP[];

void thread_process_animations(void* _){
    #ifdef DEBUG
    printf("Beginning thread_update_animation\n");
    printf("Initializing effects\n");
    #endif

    uint num_effects = 4;
    AnimatedLightingEffect* effects[num_effects];
    int dir = 1;
    // ColorPulse* sqf_ptr = new ColorPulse(LED_STRIP, 64, CHSV(180, 255, 251), 20);
    SolidFill* sf_ptr = new SolidFill(LED_STRIP, 64, CRGB(0, 0, 0));
    effects[0] = sf_ptr;
    for (int i = 1; i < num_effects; i++){
        if (i > 1){
            //BaseSequential* sqf_ptr = new BaseSequential(LED_STRIP, 64, CRGB(100, 0, 255), 64, 128, 8, (63 * (i-2)), dir);
            SequentialComet* sqf_ptr = new SequentialComet(LED_STRIP, 64, CRGB(100, 0, 255), 100, 170, 8, (63 * (i-2)), dir, 4);
            effects[i] = sqf_ptr;
            dir *= -1;
        }
        // else if (i == 3){
        //     SequentialComet* sqf_ptr = new SequentialComet(LED_STRIP, 64, CRGB(100, 0, 255), 64, 128, 8, (63 * (i-2)), dir, 4);
        //     effects[i] = sqf_ptr;
        // }
        else{
            Twinkle* t_ptr = new Twinkle(LED_STRIP, 64, CRGB(0, 50, 0), 500, 16);
            effects[i] = t_ptr;
        }
    }

    uint32_t cur_time;
    uint32_t last_displayed = 0;

    #ifdef DEBUG
    printf(" Number of running effects: %d\n", num_effects);
    printf("Start animation update loop\n");
    #endif

    while(true){
        cur_time = millis();
        // animation computation
        for (int i = 0; i < num_effects; i++){
            effects[i]->update_after_delay(cur_time);
            if (effects[i]->get_status() == DONE){
                effects[i]->reset();
                #ifdef DEBUG
                printf("Resetting effect %d\n", i);
                #endif
            }
        }

        // Only update display once every ~3 loops
        if (cur_time - last_displayed > 32){
            last_displayed = cur_time;
            for (int i = 0; i < num_effects; i++){
                effects[i]->draw_frame();
            }
            FastLED.show();
        }
        vTaskDelay(10);
    }
}
