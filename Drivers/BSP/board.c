#include "board.h"
#include "stm32f10x.h"

#define LED_PIN (1U << 13)

static void gpio_init(void)
{
    // Enable GPIOC clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // Configure PC13 as general purpose output push-pull
    // CNF13[1:0]=00 MODE13[1:0]=11 (output 50MHz)
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |=  (0x3 << 20);
}

void board_init(void)
{
    gpio_init();
}

void board_toggle_led(void)
{
    GPIOC->ODR ^= LED_PIN;
}