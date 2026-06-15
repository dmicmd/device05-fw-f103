#include <stdint.h>
#include "stm32f103xb.h"
#include "event.h"

/*
 * 32-key matrix (8x4)
 * Platform-specific GPIO access lives here (STM32F103)
 */

#define ROWS 8
#define COLS 4
#define KEY_COUNT (ROWS * COLS)

#define DEBOUNCE_MS 20

static event_queue_t *s_queue = 0;

static uint8_t stable_state[KEY_COUNT];
static uint8_t last_state[KEY_COUNT];
static uint8_t debounce_cnt[KEY_COUNT];

static uint32_t s_now_ms = 0;

/*
 * NOTE: These GPIO mappings are placeholders until full board matrix mapping is defined
 */
static uint8_t read_key_raw(uint8_t key)
{
    /*
     * TODO: map key index -> GPIO row/col scan
     * For now: return 0 (no press)
     */
    (void)key;
    return 0;
}

void keyboard_scan_set_time(uint32_t ms)
{
    s_now_ms = ms;
}

void keyboard_scan_init(event_queue_t *q)
{
    s_queue = q;

    for (uint8_t i = 0; i < KEY_COUNT; i++)
    {
        stable_state[i] = 0;
        last_state[i] = 0;
        debounce_cnt[i] = 0;
    }
}

static void emit_event(uint8_t key, uint8_t pressed)
{
    if (!s_queue) return;

    key_event_t e;
    e.key_id = key;
    e.timestamp_ms = s_now_ms;
    e.source = 0;
    e.type = pressed ? EVENT_KEY_DOWN : EVENT_KEY_UP;

    event_push(s_queue, e);
}

void keyboard_scan_task(void)
{
    for (uint8_t i = 0; i < KEY_COUNT; i++)
    {
        uint8_t raw = read_key_raw(i);

        if (raw != last_state[i])
        {
            debounce_cnt[i] = 0;
            last_state[i] = raw;
        }
        else
        {
            if (debounce_cnt[i] < DEBOUNCE_MS)
                debounce_cnt[i]++;
            else
            {
                if (stable_state[i] != raw)
                {
                    stable_state[i] = raw;
                    emit_event(i, raw);
                }
            }
        }
    }
}