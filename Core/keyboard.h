#pragma once
#include <stdint.h>
#include "event.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_DEBOUNCE_MS 20
#define KEY_COUNT 32

void keyboard_init(void);
void keyboard_update(void);

void keyboard_set_event_queue(event_queue_t *q);

#ifdef __cplusplus
}
#endif