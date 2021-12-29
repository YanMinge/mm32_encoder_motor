#include "stdio.h"
#include "stdint.h"
#include "drv_gpio.h"
#include "drv_uart.h"
#include "drv_ring_buf.h"
#include "drv_timer.h"
#include "encoder_motor.h"
#include "indicator_led.h"
#include "protocol_parse.h"
#include "drv_flash.h"

static void hardware_init(void)
{
    drv_gpio_pin_mode(PA_0, GPIO_MODE_INPUT_ANALOG);
    drv_gpio_pin_mode(PA_1, GPIO_MODE_INPUT_ANALOG);
    drv_gpio_pin_mode(PA_4, GPIO_MODE_INPUT_ANALOG);
    drv_gpio_pin_mode(PA_5, GPIO_MODE_INPUT_ANALOG);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

int main(void)
{
    systick_init();
    uart_ringbuf_init();
    drv_uart1_init(115200);

    indicator_led_init();
    set_led_color(0,0,0);
    motor_init();
    load_usr_config();
    if(usr_config_data.device_id == 0xff)
    {
        usr_config_data.device_id = device_hw_id;
        write_usr_config(usr_config_data);
    }
    device_hw_id = usr_config_data.device_id;
    hardware_init();
    drv_uart_printf(UART1, "hello encode motor:%d\r\n", device_hw_id);
    unsigned long current_time = millis();
    while(1)
    {
        if(millis() - current_time > 1000)
        {
            static bool led_state = false;
            led_state = !led_state;
            if(led_state)
            {
                drv_uart_printf(UART1, "G128 M1 R200 G100 B200 L100 X0\r\n");
            }
            else
            {
                drv_uart_printf(UART1, "G128 M1 R200 G100 B200 L0 X0\r\n");
            }
            current_time = millis();
        }
        adc_update();
        delay_ms(5);
    }
}
