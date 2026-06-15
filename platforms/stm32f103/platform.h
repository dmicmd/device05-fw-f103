#pragma once
#include <stdint.h>
#include "stm32f103xb.h"

#ifdef __cplusplus
extern "C" {
#endif

void platform_init(void);

uint32_t platform_millis(void);
void platform_delay_ms(uint32_t ms);

void platform_gpio_led_toggle(void);

// keyboard scan abstraction
void platform_keyboard_scan(uint8_t *state_out, uint8_t max_keys);

#ifdef __cplusplus
}
#endif