/*
 * Smart_Home.c
 *
 * Created: 9/7/2024 10:21:53 PM
 * Author : Team 10 
 */ 
#define F_CPU 1000000U

#include "main.h"

STD_ReturnType status = RET_OK; 
GPIO_PIN_CONFIG _pin = {.pin_direction = GPIO_PIN_OUTPUT,.pin_logic = GPIO_PIN_LOGIC_LOW ,.pin_num = GPIO_PIN0 , .pin_port = GPIO_PORTD };

int main(void)
{	
	Initialize();
    /* Replace with your application code */
    while (1) 
    {
		status = GPIO_PIN_Toggle_logic(&_pin);
		_delay_ms(500);
    }
	return 0 ;
}

void Initialize (void){
	status = GPIO_PIN_Initialize(&_pin);
}



