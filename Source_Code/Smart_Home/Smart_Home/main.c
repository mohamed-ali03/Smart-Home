/*
 * Smart_Home.c
 *
 * Created: 9/7/2024 10:21:53 PM
 * Author : Team 10 
 */ 
#include "main.h"

uint8 var ;
int main(void)
{
	Initialize();
	USART_SendStr("Welcome\n\r");
    while (1) 
    {	
		wholeProject();
    }
	return 0 ;
}

void wholeProject(void){
	// computer vision part
	if (cam_status == Face_Detected){
		USART_SendStr("Door is opened using Face Detection\n\r");
		Open_Door();
		cam_status = No_one ;
	}	
	else if (cam_status == Face_Not_Detected) {
		USART_SendStr("Welcome\n\r");
		USART_SendStr("Your are not in the data base. please enter the password on keypad\n\r");
		status = Keypad_Get_Check_Password(&keypad__,&EnterPass,&IsPassTrue,&cam_status);
		if(IsPassTrue){
			USART_SendStr("Door is opened using password\n\r");
			status = Buzzer_Stop(&buzzer_);
			Open_Door();
		}
		else {
			USART_SendStr("password is not True .Please Try again\n\r");
			status = Buzzer_Play(&buzzer_);
		}
		cam_status = No_one;
	}
	else if (cam_status == No_one )
	{
		Close_Door();
	}
	
	if(PIR_Flag){
		Temperature();
		Lighting();
	}
}
			
																		/* Initialize all Modules and devices */
void Initialize (void){
	// Internal peripherals
	status = PWM_Init(&PWM);			// Lighting control and fan motor using PWM with timer1			
	PWM_init_Timer2();					// servo motor using PWM with timer2
	status = ADC_Initialize(&adc);		// temperature and lighting sensor using ADC
	USART_Init(&usart);						// communicate with virtual terminal 
	// External interrrupt
	status = INTx_Initialize(&PIR_Sensor);		// motion sensor using external interrrupt(INT)
	// output moduls
	status = RGB_LED_INIT(&rgb);				// RGB led init
	status = Keypad_Init(&keypad__,password);	// Keypad init 
	status = Buzzer_INIT(&buzzer_);				// Buzzer init
																					
	// intialize the status of the fan and lighing
	PWM_Write(FAN_STOP,motor_en);				// make motor off at begin
	PWM_Write(0,lighting_led);					// make light off at begin 
																					
}

																					/* take the reading from the sensors  and make an action */

// INT0 : if PIR sense any motion it will set flag and enable the other sensors
void PIR_Sense(void){
	PIR_Flag = True ;
}
																					/* interaction with computer vision */
// when USART module receive 1 the interrupt will excute this function
void Open_Door(void){
		// Example: Move servo to 0 degrees
		set_servo_angle(90);

		// Example: Move servo to 90 degrees
		set_servo_angle(180);
		_delay_ms(1000);
}

void Close_Door(void){
	// Example: Move servo to 0 degrees
	set_servo_angle(90);
}
																	/* sense temperature and make an action according to it */
void Temperature(void){
	// sense the temperature of the room
	status = ADC_Read(temp_sensor,&LD35DZ_Reading);
	// Convert the ADC value to temperature in degrees Celsius.
	TMP = (uint16)(round((LD35DZ_Reading * 5.0/1023.0 - 0.5)*100));	// for tmp36
	//TMP = (uint16)(round((LD35DZ_Reading * 5.0/1023.0 )*100));			// for ld35dz
	
	//TMP = 25;
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

																			/* sense the lighing and make an action according to it */
void Lighting(void) {
	// Read lighting sensor ADC value and convert it to a percentage (0-100%) based on a 403 max value.
	status = ADC_Read(lighting_sensor,&LDR_Reading);
	led_brightness = 1023 - LDR_Reading ;
	PWM_Write(led_brightness,lighting_led);
	Light = (uint16)(100 - round(LDR_Reading * 100.0/1023.0));
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


