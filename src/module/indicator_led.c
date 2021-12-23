#include "indicator_led.h"
#include "drv_gpio.h"
#include "drv_uart.h"

void indicator_led_init(void)
{
    drv_gpio_pwm_mode(PB_5, 5000);
    drv_gpio_pwm_mode(PB_6, 5000);
    drv_gpio_pwm_mode(PB_7, 5000);
    drv_gpio_analog_write(PB_5, 1000);
    drv_gpio_analog_write(PB_6, 1000);
    drv_gpio_analog_write(PB_7, 1000);
}

void set_led_color(uint8_t red, uint8_t green, uint8_t blue)
{
    int16_t red_val = 1000 - line_map(red, 0, 1000, 0, 255);
    int16_t green_val = 1000 - line_map(green, 0, 1000, 0, 255);
    int16_t blue_val = 1000 - line_map(blue, 0, 1000, 0, 255);
    drv_gpio_analog_write(PB_5, red_val);
    drv_gpio_analog_write(PB_6, green_val);
    drv_gpio_analog_write(PB_7, blue_val);
}
