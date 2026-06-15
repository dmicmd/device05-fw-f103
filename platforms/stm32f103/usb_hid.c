#include "usb_hid.h"
#include "event.h"

/*
 * Minimal HID layer stub (will be wired to libopencm3 USB stack)
 */

void usb_hid_init(void)
{
    /* TODO: initialize USB device (libopencm3 usb stack) */
}

void usb_hid_send_key(uint8_t key_id, uint8_t pressed)
{
    /* TODO: convert key_id -> HID usage code and send report */
    (void)key_id;
    (void)pressed;
}

void usb_hid_process_event(const key_event_t *e)
{
    if (!e) return;

    usb_hid_send_key(e->key_id, (uint8_t)(e->type == EVENT_KEY_DOWN));
}