/*
 * Smart_Home.c
 *
 * Created: 9/7/2024 10:21:53 PM
 * Author : Team 10 
 */ 
#define F_CPU 1000000U

#include "main.h"

STD_ReturnType status = RET_OK ;

ADC_CONFIG adc = {.prescalar_val = ADC_PRESCALAR_2 ,.volt_ref = ADC_AVCC_VOLT_REF};

ADCx_INPUT_Channal temp_sensor = ADC6_;
ADCx_INPUT_Channal lighting_sensor = ADC7_;
INTx_CONFG	   PIR_Sensor = {.con_reg = INTx_RISING_EDGE_INTERRUPT ,.InterruptManager = PIR_Sense , .intx = INT0_};


GPIO_PIN_CONFIG led = {.pin_direction = GPIO_PIN_OUTPUT , .pin_logic = GPIO_PIN_LOGIC_LOW ,.pin_num = GPIO_PIN4 ,.pin_port = GPIO_PORTD};
	
RGB_LED rgb = {.pin0[0].pin_direction = GPIO_PIN_OUTPUT,.pin0[0].pin_logic = GPIO_PIN_LOGIC_LOW,.pin0[0].pin_num = GPIO_PIN0,.pin0[0].pin_port = GPIO_PORTD,
			   .pin0[1].pin_direction = GPIO_PIN_OUTPUT,.pin0[1].pin_logic = GPIO_PIN_LOGIC_LOW,.pin0[1].pin_num = GPIO_PIN1,.pin0[1].pin_port = GPIO_PORTD
			  };
			  
sint16 value ;
sint16 tmp   ;
uint16 light ;
uint32 flag  = 0 ;



int main(void)
{	
	Initialize();
    /* Replace with your application code */
    while (1) 
    {
		Sensors();
    }
	return 0 ;
}

void Initialize (void){
	status = GPIO_PIN_Initialize(&led);
	status = INTx_Initialize(&PIR_Sensor);
	status = ADC_Initialize(&adc);
	status = RGB_LED_INIT(&rgb);
}

// if PIR sense any motion it will set flag and enable the other sensors 
void PIR_Sense(void){
	flag = 1 ;
}


// Sensors (Temperature , lighting )
void Sensors (void){
	if(flag){
		// sense the temperature of the room
		status = ADC_Read(temp_sensor,&value);
		tmp = (uint16)(ceil(((value * 5.0/1024.0)-0.5)*100.0));
		if(tmp < 20 ){
			status = RGB_LED_BLUE(&rgb);
		}
		else if(tmp >= 20 && tmp <30) {
			status = RGB_LED_GREEN(&rgb);
		}
		else if(tmp >= 30){
			status = RGB_LED_RED(&rgb);
		}
		else {
			/*nothing*/
		}
		
		// measure the lighting of the room
		status = ADC_Read(lighting_sensor,&value);
		light = (uint16)(ceil(value * 100.0/765.0));
		if(light > 95 ){
			status = GPIO_PIN_Write_logic(&led,GPIO_PIN_LOGIC_HIGH);
		}
		else{
			status = GPIO_PIN_Write_logic(&led,GPIO_PIN_LOGIC_LOW);
		}
	}
}

