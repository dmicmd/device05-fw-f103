#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_KEYS 32

typedef enum {
    EVENT_NONE = 0,
    EVENT_KEY_DOWN,
    EVENT_KEY_UP,
    EVENT_KEY_HOLD
} event_type_t;

typedef struct {
    uint8_t key_id;
    event_type_t type;
    uint32_t timestamp_ms;
    uint8_t source; // 0 main, 1 panel1, 2 panel2
} key_event_t;

typedef struct {
    key_event_t queue[64];
    volatile uint8_t head;
    volatile uint8_t tail;
} event_queue_t;

void event_queue_init(event_queue_t *q);
uint8_t event_push(event_queue_t *q, key_event_t e);
uint8_t event_pop(event_queue_t *q, key_event_t *e);

#ifdef __cplusplus
}
#endif
