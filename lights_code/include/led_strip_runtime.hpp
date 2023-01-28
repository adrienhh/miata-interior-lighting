#ifndef LED_STRIP_RUNTIME_HPP
#define LED_STRIP_RUNTIME_HPP

#include "pulse_e.hpp"
#include "color_fade_e.hpp"
#include "sequential_e.hpp"
#include "solid_fill.hpp"
#include "twinkle.hpp"

void thread_init_effects(void* _);

void thread_update_strip(void* _);

void thread_update_animations(void* _);

#endif
