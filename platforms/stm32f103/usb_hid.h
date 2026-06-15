#pragma once
#include <stdint.h>
#include "event.h"

#ifdef __cplusplus
extern "C" {
#endif

void usb_hid_init(void);
void usb_hid_send_key(uint8_t key_id, uint8_t pressed);
void usb_hid_process_event(const key_event_t *e);

#ifdef __cplusplus
}
#endif
