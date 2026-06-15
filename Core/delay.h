#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint32_t g_systick_ms;

void delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif