/*
 * Internal_Interrupt.h
 *
 * Created: 9/8/2024 8:36:43 PM
 *  Author: mo ali
 */ 


#ifndef INTERNAL_INTERRUPT_H_
#define INTERNAL_INTERRUPT_H_

/*---------------Includes--------------*/
#include "Interrupt_CFG.h"

/*---------------------------Macro Declaration------------------------------*/
		/*--------------------------ADC Module---------------------------*/
#define ADC_INTERRUPT_ENBALE()				(SET_BIN(ADCSRA,BIT3))
#define ADC_INTERRUPT_DISABLE()				(RESET_BIN(ADCSRA,BIT3))

#define ADC_SET_FLAG()						(SET_BIN(ADCSRA,BIT4))
#define ADC_CLEAR_FLAG()					(RESET_BIN(ADCSRA,BIT4))






#endif /* INTERNAL_INTERRUPT_H_ */