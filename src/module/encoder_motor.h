#ifndef __ENCODER_MOTOR_H__
#define __ENCODER_MOTOR_H__
#include "stdint.h"
#include "stdbool.h"

void motor_init(void);
void set_motor_stop(void);
void enable_motor(bool enable);
void set_motor_pwm(uint16_t pwm);

#endif //__ENCODER_MOTOR_H__