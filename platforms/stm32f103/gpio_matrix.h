#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MATRIX_ROWS 8
#define MATRIX_COLS 4

void gpio_matrix_init(void);
uint8_t gpio_matrix_read(uint8_t row, uint8_t col);

#ifdef __cplusplus
}
#endif
