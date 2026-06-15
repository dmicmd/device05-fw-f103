#include "gpio_matrix.h"
#include "stm32f103xb.h"

/*
 * Mapping:
 * Rows: PC0-PC7 (outputs)
 * Cols: PB0-PB3 (inputs pull-up)
 */

static void delay_nop(void)
{
    for (volatile int i = 0; i < 50; i++) __asm volatile("nop");
}

void gpio_matrix_init(void)
{
    /* Enable clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN;

    /* Configure PC0-PC7 output push-pull 50MHz */
    for (int i = 0; i < 8; i++)
    {
        GPIOC->CRL &= ~(0xF << (i * 4));
        GPIOC->CRL |=  (0x3 << (i * 4));
    }

    /* Configure PB0-PB3 input pull-up */
    for (int i = 0; i < 4; i++)
    {
        GPIOB->CRL &= ~(0xF << (i * 4));
        GPIOB->CRL |=  (0x8 << (i * 4)); // input pull-up/down
        GPIOB->ODR |= (1 << i);         // pull-up
    }

    /* idle state: all rows high */
    GPIOC->ODR |= 0xFF;
}

uint8_t gpio_matrix_read(uint8_t row, uint8_t col)
{
    if (row >= 8 || col >= 4)
        return 0;

    /* Drive all rows high */
    GPIOC->ODR |= 0xFF;

    /* Pull selected row low */
    GPIOC->ODR &= ~(1 << row);

    delay_nop();

    /* Read column */
    uint8_t val = (GPIOB->IDR >> col) & 1;

    /* active low (pressed = 0) */
    return (val == 0);
}