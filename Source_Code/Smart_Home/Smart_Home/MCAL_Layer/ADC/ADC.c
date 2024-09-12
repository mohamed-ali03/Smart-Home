/*
 * ADC.c
 *
 * Created: 9/8/2024 8:01:10 PM
 *  Author: mo ali
 */ 

#include "ADC.h"


STD_ReturnType ADC_Initialize(const ADC_CONFIG* ADC_obj){
	STD_ReturnType status = RET_OK;
	if(NULL == ADC_obj )
	{
		status = RET_NOT_OK;
	}
	else {	
		// Disable ADC Module 
		ADC_DISABLE();
		// Select voltage reference
		ADC_SELECT_REFF(ADC_obj->volt_ref);		
		// Select the Prescalar Value
		ADC_SELECT_PRESCALAR_VALUE(ADC_obj->prescalar_val);
		// Configure pins(PC0:PC5) as input pins
		//DDRC = 0x00;
		//Enable ADC Module
		ADC_ENABLE();
	}
	return status ;
}

STD_ReturnType ADC_DEInitialize(const ADC_CONFIG* ADC_obj){
	STD_ReturnType status = RET_OK;
	if(NULL == ADC_obj )
	{
		status = RET_NOT_OK;
	}
	else {
		// Disable ADC Module
		ADC_DISABLE();
	}
	return status ;
}

STD_ReturnType ADC_Read(ADCx_INPUT_Channal channal,sint16 *data){
	STD_ReturnType status = RET_OK;
	if(NULL == data)
	{
		status = RET_NOT_OK;
	}
	else {
		// Configure the required pin as analog input
		ADCx_SELECT_PIN(channal);
		// Start Conversion
		ADC_START_CONVERSION();
		// wait 
		while(ADCSRA & (1 << BIT6));
		// get the reading
		*data = ADC;
	}
	return status ;
}






