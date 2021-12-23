#ifndef __INDICATOR_LED_H__
#define __INDICATOR_LED_H__
#include "stdint.h"
#include "stdbool.h"

void indicator_led_init(void);
void set_led_color(uint8_t red, uint8_t green, uint8_t blue);

#endif //__INDICATOR_LED_H__