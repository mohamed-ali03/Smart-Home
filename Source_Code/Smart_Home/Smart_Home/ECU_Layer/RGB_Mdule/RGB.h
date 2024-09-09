/*
 * IncFile1.h
 *
 * Created: 9/9/2024 11:30:49 AM
 *  Author: mo ali
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "../../MCAL_Layer/GPIO.h"

typedef struct{
	GPIO_PIN_CONFIG pin0[2] ;
}RGB_LED;

STD_ReturnType RGB_LED_INIT(const RGB_LED * _RGB_LED_Obj);
STD_ReturnType RGB_LED_OFF(const RGB_LED * _RGB_LED_Obj);
STD_ReturnType RGB_LED_RED(const RGB_LED * _RGB_LED_Obj);
STD_ReturnType RGB_LED_BLUE(const RGB_LED * _RGB_LED_Obj);
STD_ReturnType RGB_LED_GREEN(const RGB_LED * _RGB_LED_Obj);



#endif /* INCFILE1_H_ */