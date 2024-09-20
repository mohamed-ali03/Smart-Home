/*
 * PWM.h
 *
 * Created: 9/10/2024 1:56:18 PM
 *  Author: mo ali
 */ 


#ifndef PWM_H_
#define PWM_H_

/*--------------------------------Includes--------------------------------------*/
#include "../GPIO.h"

/*--------------------------------Macro Declaration---------------------------------*/

/*--------------------------------Macro Functions---------------------------------*/
// Define OC1A/OC1B in Fast PWM
#define PWM_SELECT_PWM_PIN_OC1A(x)							(TCCR1A = (TCCR1A & 0x3F) | (x << BIT6))
#define PWM_SELECT_PWM_PIN_OC1B(x)							(TCCR1A = (TCCR1A & 0xCF) | (x << BIT4))

//Clock Select Bit Description
#define PWM_SELECT_CLOCK(x)									(TCCR1B = (TCCR1B & 0xF7) | (x << BIT0))

// Set the top value 
#define PWM_SET_TOP(x)										(ICR1 = x)

#define PWM_SET_DUTY_CYCLE_OCR1A(x)								(OCR1A = x)
#define PWM_SET_DUTY_CYCLE_OCR1B(x)								(OCR1B = x)


/*--------------------------------Data Type---------------------------------*/
typedef enum {
	NORMAL_PORT_OPERATION ,				//Normal port operation, OC1A/OC1B disconnected.
	TOGGLE_OC1A_DIACONNECT_OC1B,		//WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected	(normal port operation). For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected
	CLEAR_SET,							//Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM,(non-inverting mode)
	SET_CLEAR							//Set OC1A/OC1B on Compare Match, clear OC1A/OC1B at BOTTOM,(inverting mode)
}PWM_COMPARE_OUTPUT_MODE;

typedef enum {
	PWM_PIN_OC1A , 
	PWM_PIN_OC1B
}PWM_PIN;

typedef enum {
	PWM_NO_CLOCK ,					//No clock source. (Timer/Counter stopped)
	PWM_WITH_PRESCALAR_1,			//clkI/O/1 (No prescaling)
	PWM_WITH_PRESCALAR_8,			//clkI/O/8 (From prescaler)
	PWM_WITH_PRESCALAR_64,			//clkI/O/64 (From prescaler)
	PWM_WITH_PRESCALAR_256,			//clkI/O/256 (From prescaler)
	PWM_WITH_PRESCALAR_1024,		//clkI/O/1024 (From prescaler)
	PWM_EXT_T1PIN_FALLING_EDGE,		//External clock source on T1 pin. Clock on falling edge.
	PWM_EXT_T1PIN_RISING_EDGE		//External clock source on T1 pin. Clock on rising edge
}PWM_CLOCK;

typedef struct {
	PWM_COMPARE_OUTPUT_MODE  out_mode;
	PWM_CLOCK		sel_clk ;
}PWM_CONFIG;
/*--------------------------------Function---------------------------------*/

STD_ReturnType PWM_Init(const PWM_CONFIG *pwm_obj);
void PWM_Write(uint16 dutyCycle,PWM_PIN _pin);


#endif /* PWM_H_ */