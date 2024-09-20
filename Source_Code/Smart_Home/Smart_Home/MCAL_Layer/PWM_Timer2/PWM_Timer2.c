/*
 * PWM_Timer0.c
 *
 * Created: 9/16/2024 1:33:44 AM
 *  Author: mo ali
 */ 
#include "PWM_Timer2.h"

void PWM_init_Timer2(void)
{
	// Set PB3 (OC2) as output
	DDRB |= (1 << PB3);

	TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS22);

	// Initialize with a neutral position for the servo (~1.5ms pulse)
	OCR2 = 16;  // This gives approximately a 1.5ms pulse width (servo's neutral position)
}

// Function to set the servo angle
void set_servo_angle(uint8 angle)
{
	uint8 duty_cycle = ((angle * 16) / 180) + 16;
	
	OCR2 = duty_cycle;
}