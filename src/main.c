#include "stdio.h"
#include "stdint.h"
#include "drv_gpio.h"
#include "drv_uart.h"
#include "drv_ring_buf.h"
#include "drv_timer.h"
#include "encoder_motor.h"
#include "indicator_led.h"

int main(void)
{
    systick_init();
    uart_ringbuf_init();
    drv_uart1_init(115200);

    drv_gpio_pin_mode(PA_0, GPIO_MODE_INPUT_ANALOG);
    drv_gpio_pin_mode(PA_1, GPIO_MODE_INPUT_ANALOG);
    drv_gpio_pin_mode(PA_4, GPIO_MODE_INPUT_ANALOG);
    drv_gpio_pin_mode(PA_5, GPIO_MODE_INPUT_ANALOG);
   
    indicator_led_init();
    set_led_color(0,0,0);
    motor_init();
    set_motor_pwm(500);

    drv_uart_printf(UART1, "hello yanminge\r\n");
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    unsigned long current_time = millis();
    while(1)
    {
        if(millis() - current_time > 1000)
        {
            static bool led_state = LOW;
            led_state = !led_state;
            drv_uart_printf(UART1, "PB_5 led_state: %d, adc read: %d, %d, %d, %d\n", led_state, drv_gpio_analog_read(PA_0), drv_gpio_analog_read(PA_1), drv_gpio_analog_read(PA_4), drv_gpio_analog_read(PA_5));
            current_time = millis();
        }
        adc_update();
        delay_ms(5);
    }
}