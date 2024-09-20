
/*
 * main.h
 *
 * Created: 9/7/2024 10:52:35 PM
 *  Author: Team 10 
 */ 

/*---------------------------------includes --------------------------------*/
#define F_CPU 8000000UL      // CPU frequency set to 8 MHz
#include "MCAL_Layer/MCAL_Modules.h"
#include "ECU_Layer/ECU_Devices.h"


/*--------------------------------------Function Declaration-----------------------------------*/
// Initialize all Modules and devices 
void Initialize (void);
// take the reading from the sensors  and make an action
void PIR_Sense(void);
void Temperature(void);
void Lighting(void);
// function to open the door
void Open_Door(void);
// print status 
void PrintStatus(void);
// convert int to string 
void ShortToString(sint16 num, uint8 *str);


// important variables
sint16 LD35DZ_Reading ;
sint16 TMP   ;
uint16 motor_speed;

sint16 LDR_Reading;
uint16 Light ;
uint16 led_brightness;

bool PIR_Flag  = False ;	// if there is a motion or not

Camera_status cam_status =  No_one ;  // indicator if the door is opened or close

bool IsPassTrue = False;	// indicator if entered password to keypad is true or false

uint8 str_status[6] = {0};	// storage memory that will store (tmp,lighting,motor speed) as string

bool Buzzer_Flag = True ;

uint8 EnterPass[5];
uint8 *password = "1234";

double count = 0 ;

/*-------------------------------Macro Declaration-----------------------------*/
#define FAN_MAX_SPEED		1023
#define FAN_STOP		    0

/*------------------------------Data Type------------------------------*/
STD_ReturnType status = RET_OK ;
												// modules // 
// ADC Declaration
ADC_CONFIG adc = {.prescalar_val = ADC_PRESCALAR_2 ,.volt_ref = ADC_AVCC_VOLT_REF};
	
// make OC1A and OC1B generate PWM to lighting control and fan motor 
PWM_CONFIG PWM = {.out_mode = CLEAR_SET ,.sel_clk  = PWM_WITH_PRESCALAR_1};
	
// USART Module
USART_Config usart = {.interruptReceive = Open_Door ,.computer_vision_cam = &cam_status};

												// Input //
// Sensors Declaration (temperature , lighting , Motion
ADCx_INPUT_Channal temp_sensor = ADC4_;
ADCx_INPUT_Channal lighting_sensor = ADC5_;

INTx_CONFG	   PIR_Sensor = {.con_reg = INTx_RISING_EDGE_INTERRUPT ,.InterruptManager = PIR_Sense , .intx = INT0_};
	
Keypad_Config keypad__ = {.Rows[0].pin_direction = GPIO_PIN_INPUT,.Rows[0].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[0].pin_num = GPIO_PIN0 ,.Rows[0].pin_port = GPIO_PORTC,
						  .Rows[1].pin_direction = GPIO_PIN_INPUT,.Rows[1].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[1].pin_num = GPIO_PIN1 ,.Rows[1].pin_port = GPIO_PORTC,
						  .Rows[2].pin_direction = GPIO_PIN_INPUT,.Rows[2].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[2].pin_num = GPIO_PIN2 ,.Rows[2].pin_port = GPIO_PORTC,
						  .Rows[3].pin_direction = GPIO_PIN_INPUT,.Rows[3].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Rows[3].pin_num = GPIO_PIN3 ,.Rows[3].pin_port = GPIO_PORTC,
						  .Columns[0].pin_direction = GPIO_PIN_OUTPUT,.Columns[0].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Columns[0].pin_num = GPIO_PIN5 ,.Columns[0].pin_port = GPIO_PORTB,
						  .Columns[1].pin_direction = GPIO_PIN_OUTPUT,.Columns[1].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Columns[1].pin_num = GPIO_PIN6 ,.Columns[1].pin_port = GPIO_PORTB,
						  .Columns[2].pin_direction = GPIO_PIN_OUTPUT,.Columns[2].pin_logic = GPIO_PIN_LOGIC_HIGH ,.Columns[2].pin_num = GPIO_PIN7 ,.Columns[2].pin_port = GPIO_PORTB,
						  };
	
												// Output //
// Output dependent on sensors 
PWM_PIN motor_en = PWM_PIN_OC1A ;
PWM_PIN lighting_led = PWM_PIN_OC1B ;

// RGB Declaration - Indicate the temperature 
RGB_LED rgb = {.pin0[0].pin_direction = GPIO_PIN_OUTPUT,.pin0[0].pin_logic = GPIO_PIN_LOGIC_LOW,.pin0[0].pin_num = GPIO_PIN4,.pin0[0].pin_port = GPIO_PORTD,
				.pin0[1].pin_direction = GPIO_PIN_OUTPUT,.pin0[1].pin_logic = GPIO_PIN_LOGIC_LOW,.pin0[1].pin_num = GPIO_PIN5,.pin0[1].pin_port = GPIO_PORTD
};


Buzzer_Config buzzer_ = {.buzzer.pin_direction = GPIO_PIN_OUTPUT , .buzzer.pin_logic = GPIO_PIN_LOGIC_LOW , .buzzer.pin_num = GPIO_PIN0,.buzzer.pin_port = GPIO_PORTB};







