#include "delay.h"

void delay_ms(uint32_t ms)
{
    uint32_t start = g_systick_ms;
    while ((g_systick_ms - start) < ms)
    {
        __asm volatile("nop");
    }
}