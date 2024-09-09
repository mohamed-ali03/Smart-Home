/*
 * ADC.h
 *
 * Created: 9/8/2024 8:00:06 PM
 *  Author: mo ali
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../Interrupt/Internal_Interrupt.h"
#include "../GPIO.h"

/*------------------------------------Macro Functions-----------------------------------*/
// ADC Enable and Disable 
#define ADC_ENABLE()					(SET_BIN(ADCSRA,BIT7))
#define ADC_DISABLE()					(RESET_BIN(ADCSRA,BIT7))

// ADC Start and Stop Conversion
#define ADC_START_CONVERSION()					(SET_BIN(ADCSRA,BIT6))
#define ADC_STOP_CONVERSION()					(RESET_BIN(ADCSRA,BIT6))

// ADC Select Prescalar Value 
#define ADC_SELECT_PRESCALAR_VALUE(x)			(ADCSRA = (ADCSRA & 0xF8) | (x & 0x07))

// ADC Free Running Select
#define ADC_FREE_RUNNING_ENABLE()					(SET_BIN(ADCSRA,BIT5))
#define ADC_FREE_RUNNING_DISABLE()					(RESET_BIN(ADCSRA,BIT5))

// Analog Channel Selection Bits
#define	ADCx_SELECT_PIN(x)				(ADMUX = (ADMUX & 0xF0) | (x & 0x0F))
// Voltage Reference Selections for ADC
#define ADC_SELECT_REFF(x)				(ADMUX = (ADMUX & 0x3F) |( x << BIT6))
// ADC Left Adjust Result
#define ADC_LEFT_ADJUST()				(SET_BIN(ADMUX,BIT5))
#define ADC_RIGHT_ADJUST()				(RESET_BIN(ADMUX,BIT5))


/*------------------------------------Data Type-----------------------------------*/
typedef enum {
	ADC_FREE_OFF,
	ADC_FREE_ON
}ADC_RUNNING_STATUS;

typedef enum{
	ADC_LEFT_AD,
	ADC_RIGHT_AD
}ADC_ADJUST;


typedef enum {
	ADC_PRESCALAR_2 = 1,
	ADC_PRESCALAR_4,
	ADC_PRESCALAR_8,
	ADC_PRESCALAR_16,
	ADC_PRESCALAR_32,
	ADC_PRESCALAR_64,
	ADC_PRESCALAR_128
}ADC_PRESCALAR_VALUES;

typedef enum {
	ADC0_ ,
	ADC1_ ,
	ADC2_ ,
	ADC3_ ,
	ADC4_ ,
	ADC5_ ,
	ADC6_ ,
	ADC7_ ,
	VBG_30V = 14,
	GND 
}ADCx_INPUT_Channal;

typedef enum{
	ADC_AREF_VOLT_REF,	 // AREF, Internal Vref turned off
	ADC_AVCC_VOLT_REF,  // AVCC with external capacitor at AREF pin
	RESERVED ,
	ADC_INTERNAL_VOLT_REF	//Internal 2.56V Voltage Reference with external capacitor at AREF pin
}ADC_VOLTAGE_REF;

typedef struct{
	ADC_VOLTAGE_REF			volt_ref;
	ADC_PRESCALAR_VALUES	prescalar_val;
}ADC_CONFIG;

/*-----------------------------------------Functions-----------------------------------------------*/
STD_ReturnType ADC_Initialize(const ADC_CONFIG* ADC_obj);
STD_ReturnType ADC_DEInitialize(const ADC_CONFIG* ADC_obj);
STD_ReturnType ADC_Read(ADCx_INPUT_Channal channal,sint16 *data);



#endif /* ADC_H_ */