/*
 * Buzzer.c
 *
 * Created: 9/11/2024 7:33:02 PM
 *  Author: mo ali
 */ 

#include "Buzzer.h"


STD_ReturnType Buzzer_INIT(const Buzzer_Config *Buzzer_obj){
	STD_ReturnType status = RET_OK ;
	if (NULL == Buzzer_obj){
		status = RET_NOT_OK;
	}
	else {
		status = GPIO_PIN_Initialize(&(Buzzer_obj->buzzer));
	}
	return status ;
}
STD_ReturnType Buzzer_Play(const Buzzer_Config *Buzzer_obj){
	STD_ReturnType status = RET_OK ;
	if (NULL == Buzzer_obj){
		status = RET_NOT_OK;
	}
	else {
		status = GPIO_PIN_Write_logic(&(Buzzer_obj->buzzer),GPIO_PIN_LOGIC_HIGH);
	}
	return status ;
}
STD_ReturnType Buzzer_Stop(const Buzzer_Config *Buzzer_obj){
	STD_ReturnType status = RET_OK ;
	if (NULL == Buzzer_obj){
		status = RET_NOT_OK;
	}
	else {
		status = GPIO_PIN_Write_logic(&(Buzzer_obj->buzzer),GPIO_PIN_LOGIC_LOW);
	}
	return status ;
}
