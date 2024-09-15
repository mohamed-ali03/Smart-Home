/*
 * Smart_Home.c
 *
 * Created: 9/7/2024 10:21:53 PM
 * Author : Team 10 
 */ 
#include "main.h"
uint8 *password = "1234";


int main(void)
{
	Initialize();
	USART_SendStr("Welcome , Enter the password on Keypad \n\r");
    /* Replace with your application code */
    while (1) 
    {
		// disable the keypad if the user enter the password true
		if(!IsPassTrue){
			status = Keypad_Get_Check_Password(&keypad__,EnterPass,&IsPassTrue,&Door_Flag);
		}
		
		if(IsPassTrue || Door_Flag){
			// make the door open and close one time 
			if(flag){
				Open_Door();
				if(Door_Flag){
					USART_SendStr("Door is opened using face detection. Welcome to your Home (: \n\r");
				}
				else if(IsPassTrue){
					USART_SendStr("Door is opened using Password . Welcome to your Home (: \n\r");
				}
				status = Buzzer_Stop(&buzzer_);
				flag = False;
			}
			
			// if anyone in the house get sense from the sensors 
			if (PIR_Flag){
				Temperature();
				Lighting();
			}
			
			// send the status(Temp , Light , Fan Speed) to virtual terminal using USART
			PrintStatus();
		}
		else{
			USART_SendStr("Password is wrong ,Try again\n\r");
			// if you enter the password wrong three times the buzzer will play 
			status = Buzzer_Play(&buzzer_);
		}
    }
	return 0 ;
}


																					/* Initialize all Modules and devices */
void Initialize (void){
	// Internal peripherals 
	status = PWM_Init(&PWM);
	PWM_Write(led_brightness,lighting_led);
	status = ADC_Initialize(&adc);
	USART_Init();
	// External interrrupt
	status = INTx_Initialize(&PIR_Sensor);
	status = INTx_Initialize((&Door_Status));
	// output moduls 
	status = RGB_LED_INIT(&rgb);
	status = Door_Motor_Init(&door_motor);
	status = Keypad_Init(&keypad__,password);
	status = Buzzer_INIT(&buzzer_);
}

																					/* take the reading from the sensors  and make an action */

// INT0 : if PIR sense any motion it will set flag and enable the other sensors
void PIR_Sense(void){
	PIR_Flag = True ;
}
																					/* interaction with computer vision */
// INT1 : when we need to open the door
void Door_OpenCV(void){
	Door_Flag = True ;
}

void Temperature(void){
	// sense the temperature of the room
	status = ADC_Read(temp_sensor,&value);
	// Convert the ADC value to temperature in degrees Celsius.
	TMP = (uint16)(round(((value * 5.0/1024.0)-0.5)*100.0));
	// choose the suitable state
	if(TMP < 20 ){
		motor_speed =  FAN_STOP ;
		PWM_Write(motor_speed,motor_en);
		status = RGB_LED_BLUE(&rgb);
	}
	else if(TMP >= 20 && TMP <=30) {
		motor_speed = (uint16)(round(512 + (TMP-20) * 511/10.0) );
		PWM_Write(motor_speed,motor_en);
		status = RGB_LED_GREEN(&rgb);
	}
	else if(TMP > 30){
		motor_speed = FAN_MAX_SPEED ;
		PWM_Write(motor_speed,motor_en);
		status = RGB_LED_RED(&rgb);
	}
	else {
		/*nothing*/
	}
}


void Lighting(void) {
	// Read lighting sensor ADC value and convert it to a percentage (0-100%) based on a 403 max value.
	status = ADC_Read(lighting_sensor,&value);
	Light = (uint16)(100 - round(value * 100.0/403.0));
	// Convert the light percentage (0-100%) to a PWM value (0-1023) for LED brightness control.
	led_brightness = (uint16)(round(Light *1023.0/100));
	PWM_Write(led_brightness,lighting_led);
}
															

// open door
void Open_Door(void){
	status = Door_Motor_Open(&door_motor);
	_delay_ms(3000);
	status = Door_Motor_Stop(&door_motor);
	_delay_ms(10000);
	status = Door_Motor_Close(&door_motor);
	_delay_ms(3000);
	status = Door_Motor_Stop(&door_motor);
}

																			/* Interact with virtual terminal */
// send the status(Temp , Light , Fan Speed) to virtual terminal using USART
void PrintStatus(void){
	USART_SendStr("Temperature : ");
	ShortToString(TMP,str_status);
	USART_SendStr(str_status);
	USART_SendStr(" ---------- Motor Speed : ");
	ShortToString(motor_speed,str_status);
	USART_SendStr(str_status);
	USART_SendStr(" ---------- Lighting : ");
	ShortToString(Light,str_status);
	USART_SendStr(str_status);
	USART_SendStr("\r\n");
}

																				/*Convert Integer to String */
void ShortToString(sint16 num, uint8 *str) {
	uint8 str_temp [5];
	uint16 traverse_arr  = 0;

	uint8 *str_traverse = str ;

	uint16 int_temp ;
	sint16 count ;

	if(num == 0 ){
		*str_traverse++ = '0';
		*str_traverse = '\0';
	}
	else{
		if(num < 0){
			*str_traverse++ = '-';
			*str_traverse = '\0';
			num = ~num + 1 ;					// get inverse 2th complement
		}
		
		while(num > 0){
			int_temp = num % 10;
			num /= 10 ;
			switch (int_temp){
				case 0 :str_temp[traverse_arr++] = '0';break;
				case 1 :str_temp[traverse_arr++] = '1';break;
				case 2 :str_temp[traverse_arr++] = '2';break;
				case 3 :str_temp[traverse_arr++] = '3';break;
				case 4 :str_temp[traverse_arr++] = '4';break;
				case 5 :str_temp[traverse_arr++] = '5';break;
				case 6 :str_temp[traverse_arr++] = '6';break;
				case 7 :str_temp[traverse_arr++] = '7';break;
				case 8 :str_temp[traverse_arr++] = '8';break;
				case 9 :str_temp[traverse_arr++] = '9';break;
				default :break;
				
			}
		}
	}
	
	
	
	for(count = traverse_arr-1 ; count >= 0 ; count--){
		*str_traverse++ = str_temp[count];
		*str_traverse = '\0';
	}
}


