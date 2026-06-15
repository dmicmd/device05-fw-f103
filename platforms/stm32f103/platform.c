#include "platform.h"
#include "delay.h"

extern volatile uint32_t g_systick_ms;

void platform_init(void)
{
    // GPIOC clock enable
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // LED PC13 output push-pull
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x3 << 20);
}

uint32_t platform_millis(void)
{
    return g_systick_ms;
}

void platform_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

void platform_gpio_led_toggle(void)
{
    GPIOC->ODR ^= (1U << 13);
}

void platform_keyboard_scan(uint8_t *state_out, uint8_t max_keys)
{
    if (!state_out) return;

    if (max_keys > 16) max_keys = 16;

    // Example: GPIOA input pins 0..(max_keys-1)
    for (uint8_t i = 0; i < max_keys; i++)
    {
        state_out[i] = (GPIOA->IDR & (1U << i)) ? 1 : 0;
    }
}