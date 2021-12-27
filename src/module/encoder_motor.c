#include "stdint.h"
#include "stdbool.h"
#include "encoder_motor.h"
#include "drv_gpio.h"
#include "drv_uart.h"

static bool motor_enable = false;

void motor_init(void)
{
    drv_gpio_pin_mode(PA_15, GPIO_MODE_OUTPUT);
    drv_gpio_digital_write(PA_15, LOW);
    motor_enable = false;
    drv_gpio_pwm_mode(PB_3, 5000);
    drv_gpio_pwm_mode(PB_4, 5000);
}

void set_motor_stop(void)
{
    drv_gpio_analog_write(PB_3, 1000);
    drv_gpio_analog_write(PB_4, 1000);
    drv_gpio_digital_write(PA_15, LOW);
    motor_enable = false;
}

void enable_motor(bool enable)
{
    if(enable)
    {
        drv_gpio_digital_write(PA_15, HIGH);
    }
    else
    {
        drv_gpio_digital_write(PA_15, LOW);
    }
    motor_enable = enable;
}

void set_motor_pwm(uint16_t pwm)
{
    if((pwm != 0) && (motor_enable == false))
    {
        enable_motor(true);
    }
    if(pwm == 0)
    {
        set_motor_stop();
    }
    else if(pwm > 0)
    {
        drv_gpio_analog_write(PB_4, 1000);
        drv_gpio_analog_write(PB_3, pwm);
    }
    else
    {
        drv_gpio_analog_write(PB_4, pwm);
        drv_gpio_analog_write(PB_3, 1000);
    }
}