
/*
 * main.h
 *
 * Created: 9/7/2024 10:52:35 PM
 *  Author: Team 10 
 */ 

/*---------------------------------includes --------------------------------*/

#include "MCAL_Layer/MCAL_Modules.h"
#include "ECU_Layer/ECU_Devices.h"

/*--------------------------------------Function Declaration-----------------------------------*/
// Initialize all Modules and devices 
void Initialize (void);
// take the reading from the sensors  and make an action
void PIR_Sense(void);
void Temperature(void);
void Lighting(void);
// interaction with computer vision
void Door_OpenCV(void);
// function to open the door
void Open_Door(void);
// print status 
void PrintStatus(void);
// convert int to string 
void ShortToString(sint16 num, uint8 *str);



/*-------------------------------Macro Declaration-----------------------------*/
#define F_CPU 8000000UL      // CPU frequency set to 8 MHz
#define FAN_MAX_SPEED		1023
#define FAN_STOP		    0

/*------------------------------Data Type------------------------------*/
STD_ReturnType status = RET_OK ;
												// modules // 
// ADC Declaration
ADC_CONFIG adc = {.prescalar_val = ADC_PRESCALAR_2 ,.volt_ref = ADC_AVCC_VOLT_REF};
	
// PWM Declaration
PWM_CONFIG PWM = {.out_mode = CLEAR_SET ,.sel_clk = PWM_WITH_PRESCALAR_64};

												// Input //
// Sensors Declaration (temperature , lighting , Motion
ADCx_INPUT_Channal temp_sensor = ADC6_;
ADCx_INPUT_Channal lighting_sensor = ADC7_;
INTx_CONFG	   PIR_Sensor = {.con_reg = INTx_RISING_EDGE_INTERRUPT ,.InterruptManager = PIR_Sense , .intx = INT0_};
INTx_CONFG	   Door_Status = {.con_reg = INTx_RISING_EDGE_INTERRUPT , .InterruptManager = Door_OpenCV , .intx = INT1_};
Keypad_Config keypad__ = {.Rows[0].pin_direction = GPIO_PIN_INPUT,.Rows[0].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[0].pin_num = GPIO_PIN0 ,.Rows[0].pin_port = GPIO_PORTC,
						  .Rows[1].pin_direction = GPIO_PIN_INPUT,.Rows[1].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[1].pin_num = GPIO_PIN1 ,.Rows[1].pin_port = GPIO_PORTC,
						  .Rows[2].pin_direction = GPIO_PIN_INPUT,.Rows[2].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[2].pin_num = GPIO_PIN2 ,.Rows[2].pin_port = GPIO_PORTC,
						  .Rows[3].pin_direction = GPIO_PIN_INPUT,.Rows[3].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[3].pin_num = GPIO_PIN3 ,.Rows[3].pin_port = GPIO_PORTC,
						  .Columns[0].pin_direction = GPIO_PIN_OUTPUT,.Columns[0].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Columns[0].pin_num = GPIO_PIN4 ,.Columns[0].pin_port = GPIO_PORTC,
						  .Columns[1].pin_direction = GPIO_PIN_OUTPUT,.Columns[1].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Columns[1].pin_num = GPIO_PIN5 ,.Columns[1].pin_port = GPIO_PORTC,
						  .Columns[2].pin_direction = GPIO_PIN_OUTPUT,.Columns[2].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Columns[2].pin_num = GPIO_PIN6 ,.Columns[2].pin_port = GPIO_PORTD,
						  };
	
												// Output //
// Output dependent on sensors 
PWM_PIN motor_en = PWM_PIN_OC1A ;
PWM_PIN lighting_led = PWM_PIN_OC1B ;

// RGB Declaration - Indicate the temperature 
RGB_LED rgb = {.pin0[0].pin_direction = GPIO_PIN_OUTPUT,.pin0[0].pin_logic = GPIO_PIN_LOGIC_LOW,.pin0[0].pin_num = GPIO_PIN3,.pin0[0].pin_port = GPIO_PORTB,
				.pin0[1].pin_direction = GPIO_PIN_OUTPUT,.pin0[1].pin_logic = GPIO_PIN_LOGIC_LOW,.pin0[1].pin_num = GPIO_PIN4,.pin0[1].pin_port = GPIO_PORTB
};

// Door motor 
Door_Motor_Config door_motor = {.motor_pins[0].pin_direction = GPIO_PIN_OUTPUT ,.motor_pins[0].pin_logic = GPIO_PIN_LOGIC_HIGH,.motor_pins[0].pin_num = GPIO_PIN4,.motor_pins[0].pin_port =GPIO_PORTC,
						        .motor_pins[1].pin_direction = GPIO_PIN_OUTPUT ,.motor_pins[1].pin_logic = GPIO_PIN_LOGIC_LOW,.motor_pins[1].pin_num = GPIO_PIN5,.motor_pins[1].pin_port =GPIO_PORTC};


Buzzer_Config buzzer_ = {.buzzer.pin_direction = GPIO_PIN_OUTPUT , .buzzer.pin_logic = GPIO_PIN_LOGIC_LOW , .buzzer.pin_num = GPIO_PIN7,.buzzer.pin_port = GPIO_PORTD};


// important variables
sint16 value ;
sint16 TMP   ;
uint16 motor_speed;

uint16 Light ;
uint16 led_brightness;

bool PIR_Flag  = False ;
bool Door_Flag = False ;
uint8 EnterPass[5];
bool IsPassTrue = False;
bool flag = True;			// to make the door open one time only 
uint8 str_status[6] = {0};




