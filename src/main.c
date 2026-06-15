#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <stdint.h>
#include <stdbool.h>

// =============================
// Keyboard System v1 (SRS-based skeleton)
// MCU: STM32F103
// HAL: libopencm3
// =============================

#define NUM_KEYS 32
#define DEBOUNCE_MS 20

static volatile uint32_t g_ms = 0;

// -----------------------------
// Event model
// -----------------------------
typedef enum {
    EV_KEY_PRESS,
    EV_KEY_RELEASE,
    EV_HEARTBEAT,
    EV_UART_CMD
} event_type_t;

typedef struct {
    event_type_t type;
    uint8_t id;
    uint8_t value;
} event_t;

// Simple ring buffer (placeholder)
#define EVT_Q_SIZE 64
static event_t evt_q[EVT_Q_SIZE];
static uint8_t evt_head = 0;
static uint8_t evt_tail = 0;

static void push_event(event_t e)
{
    uint8_t next = (evt_head + 1) % EVT_Q_SIZE;
    if (next != evt_tail)
    {
        evt_q[evt_head] = e;
        evt_head = next;
    }
}

static bool pop_event(event_t *e)
{
    if (evt_head == evt_tail) return false;
    *e = evt_q[evt_tail];
    evt_tail = (evt_tail + 1) % EVT_Q_SIZE;
    return true;
}

// -----------------------------
// SysTick (1ms)
// -----------------------------
void sys_tick_handler(void)
{
    g_ms++;
}

static void systick_setup(void)
{
    systick_set_reload(72000 - 1); // 1ms @ 72MHz
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();
    systick_interrupt_enable();
}

// -----------------------------
// Keyboard scan (stub)
// -----------------------------
static uint8_t key_state[NUM_KEYS];
static uint8_t key_debounce[NUM_KEYS];

static void keyboard_scan(void)
{
    // TODO: real matrix scan
    // stub: no real hardware yet
}

// -----------------------------
// USB HID (stub)
// -----------------------------
static void usb_send_key(uint8_t key, bool pressed)
{
    (void)key;
    (void)pressed;
    // TODO: implement USB HID keyboard report
}

// -----------------------------
// UART (stub)
// -----------------------------
static void uart_process(void)
{
    // TODO: parse byte-stream protocol
}

// -----------------------------
// Event processing
// -----------------------------
static void process_event(event_t *e)
{
    switch (e->type)
    {
        case EV_KEY_PRESS:
            usb_send_key(e->id, true);
            break;
        case EV_KEY_RELEASE:
            usb_send_key(e->id, false);
            break;
        case EV_HEARTBEAT:
            break;
        case EV_UART_CMD:
            break;
    }
}

// -----------------------------
// Hardware init
// -----------------------------
static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOC);

    gpio_set_mode(GPIOC,
                  GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL,
                  GPIO13);
}

static void clock_setup(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
}

int main(void)
{
    clock_setup();
    systick_setup();
    gpio_setup();

    uint32_t last_hb = 0;

    while (1)
    {
        keyboard_scan();
        uart_process();

        // heartbeat 1s
        if (g_ms - last_hb > 1000)
        {
            last_hb = g_ms;
            event_t hb = {.type = EV_HEARTBEAT, .id = 0, .value = 0};
            push_event(hb);

            gpio_toggle(GPIOC, GPIO13);
        }

        event_t e;
        while (pop_event(&e))
        {
            process_event(&e);
        }
    }
}
