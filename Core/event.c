#include "event.h"

void event_queue_init(event_queue_t *q)
{
    q->head = 0;
    q->tail = 0;
}

uint8_t event_push(event_queue_t *q, key_event_t e)
{
    uint8_t next = (uint8_t)(q->head + 1) % 64;

    if (next == q->tail)
        return 0; // full

    q->queue[q->head] = e;
    q->head = next;

    return 1;
}

uint8_t event_pop(event_queue_t *q, key_event_t *e)
{
    if (q->tail == q->head)
        return 0; // empty

    *e = q->queue[q->tail];
    q->tail = (uint8_t)(q->tail + 1) % 64;

    return 1;
}