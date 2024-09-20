/*
 * Keypad.h
 *
 * Created: 9/11/2024 2:10:14 PM
 *  Author: mo ali
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

/*-----------------------includes-----------------------*/
#include "../../MCAL_Layer/GPIO.h"
/*-----------------------Macro Declarations------------------*/

/*-----------------------Macro Functions------------------*/

/*-----------------------Data Type------------------*/
typedef struct{
	GPIO_PIN_CONFIG Rows[4];
	GPIO_PIN_CONFIG Columns[3];
	char *ActualPassword ;
}Keypad_Config;
/*-----------------------Functions Declaration------------------*/
STD_ReturnType Keypad_Init(Keypad_Config *keypad_obj,uint8 *password);
STD_ReturnType Keypad_Get_char(const Keypad_Config *keypad_obj,uint8 *_char,Camera_status *cam) ;
STD_ReturnType Keypad_Get_Check_Password(const Keypad_Config *keypad_obj,uint8 pass[],bool *ispasstrue,Camera_status *cam);






#endif /* KEYPAD_H_ */