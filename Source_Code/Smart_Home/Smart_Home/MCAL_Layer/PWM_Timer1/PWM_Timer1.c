/*
 * PWM.c
 *
 * Created: 9/10/2024 1:56:07 PM
 *  Author: mo ali
 */ 

#include "PWM_Timer1.h"

STD_ReturnType PWM_Init(const PWM_CONFIG *pwm_obj){
	STD_ReturnType status = RET_OK;
	if (NULL == pwm_obj){
		status = RET_NOT_OK;
	}
	else {
		// configure OC1A and OC1B as output pins
		SET_BIN(DDRB , BIT1); // OC1A
		SET_BIN(DDRB , BIT2); // OC1B
		
		// select fast PWM mode
		TCCR1B = (1 << WGM12);
		TCCR1A = (1 << WGM11)  | (1 << WGM10);
		
		PWM_SELECT_PWM_PIN_OC1A(0x02);
		PWM_SELECT_PWM_PIN_OC1B(0x02);
		
		// select clock source 
		PWM_SELECT_CLOCK(pwm_obj->sel_clk);
		
		// Initialze duty cycle 
		PWM_SET_DUTY_CYCLE_OCR1A(1500);
		PWM_SET_DUTY_CYCLE_OCR1B(1000);
	}
	return status ;
}

void PWM_Write(uint16 dutyCycle,PWM_PIN _pin){
	if(_pin == PWM_PIN_OC1A){
		PWM_SET_DUTY_CYCLE_OCR1A(dutyCycle);
	}
	else if(_pin == PWM_PIN_OC1B){
		PWM_SET_DUTY_CYCLE_OCR1B(dutyCycle);
	}
	else {
		/*nothing*/
	}
}
