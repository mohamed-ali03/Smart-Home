/*
 * PWM_Timer0.h
 *
 * Created: 9/16/2024 1:33:56 AM
 *  Author: mo ali
 */ 


#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_

#include "../GPIO.h"
#define F_CPU 8000000UL      // CPU frequency set to 8 MHz

void PWM_init_Timer2(void);
void set_servo_angle(uint8 angle);

#endif /* PWM_TIMER0_H_ */