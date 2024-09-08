/*
 * Smart_Home.c
 *
 * Created: 9/7/2024 10:21:53 PM
 * Author : Team 10 
 */ 
#define F_CPU 1000000U

#include "main.h"
void toggle(void);

STD_ReturnType status = RET_OK; 
GPIO_PIN_CONFIG _pin = {.pin_direction = GPIO_PIN_OUTPUT,.pin_logic = GPIO_PIN_LOGIC_LOW ,.pin_num = GPIO_PIN0 , .pin_port = GPIO_PORTD };

INTx_CONFG int0 = {.con_reg = INTx_RISING_EDGE_INTERRUPT , .InterruptManager = toggle , .intx = INT1_};
	
int main(void)
{	
	Initialize();
    /* Replace with your application code */
    while (1) 
    {
		
		
    }
	return 0 ;
}

void Initialize (void){
	status = GPIO_PIN_Initialize(&_pin);
	status = INTx_Initialize(&int0);
}


void toggle(){
	status = GPIO_PIN_Toggle_logic(&_pin);
}



