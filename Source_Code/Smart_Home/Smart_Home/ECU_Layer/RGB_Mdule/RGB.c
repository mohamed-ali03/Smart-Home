/*
 * RGB.c
 *
 * Created: 9/9/2024 11:30:42 AM
 *  Author: mo ali
 */ 
#include "RGB.h"

STD_ReturnType RGB_LED_INIT(const RGB_LED * _RGB_LED_Obj){
	STD_ReturnType status = RET_OK ;
	if (NULL ==  _RGB_LED_Obj){
		status = RET_NOT_OK ;
	}
	else {
		status = GPIO_PIN_Initialize(&(_RGB_LED_Obj->pin0[0]));
		status = GPIO_PIN_Initialize(&(_RGB_LED_Obj->pin0[1]));
	}
	return status ;
}
STD_ReturnType RGB_LED_OFF(const RGB_LED * _RGB_LED_Obj){
	STD_ReturnType status = RET_OK ;
	if (NULL ==  _RGB_LED_Obj){
		status = RET_NOT_OK ;
	}
	else {
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[0]) ,GPIO_PIN_LOGIC_LOW);
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[1]) ,GPIO_PIN_LOGIC_LOW  );
	}
	return status ;
}
STD_ReturnType RGB_LED_RED(const RGB_LED * _RGB_LED_Obj){
	STD_ReturnType status = RET_OK ;
	if (NULL ==  _RGB_LED_Obj){
		status = RET_NOT_OK ;
	}
	else {
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[0]) ,GPIO_PIN_LOGIC_HIGH );
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[1]) ,GPIO_PIN_LOGIC_LOW  );
	}
	return status ;
}

STD_ReturnType RGB_LED_BLUE(const RGB_LED * _RGB_LED_Obj){
	STD_ReturnType status = RET_OK ;
	if (NULL ==  _RGB_LED_Obj){
		status = RET_NOT_OK ;
	}
	else {
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[0]) ,GPIO_PIN_LOGIC_HIGH );
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[1]) ,GPIO_PIN_LOGIC_HIGH );
	}
	return status ;
}

STD_ReturnType RGB_LED_GREEN(const RGB_LED * _RGB_LED_Obj){
	STD_ReturnType status = RET_OK ;
	if (NULL ==  _RGB_LED_Obj){
		status = RET_NOT_OK ;
	}
	else {
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[0]) ,GPIO_PIN_LOGIC_LOW );
		status = GPIO_PIN_Write_logic(&(_RGB_LED_Obj->pin0[1]) ,GPIO_PIN_LOGIC_HIGH);
	}
	return status ;
}

