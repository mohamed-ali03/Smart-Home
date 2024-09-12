/*
 * Door_Motor.h
 *
 * Created: 9/10/2024 7:25:35 PM
 *  Author: mo ali
 */ 


#ifndef DOOR_MOTOR_H_
#define DOOR_MOTOR_H_
#include "../../MCAL_Layer/GPIO.h"




typedef struct {
	GPIO_PIN_CONFIG motor_pins[2];
}Door_Motor_Config;


STD_ReturnType Door_Motor_Init(const Door_Motor_Config * motor_obj);
STD_ReturnType Door_Motor_Open(const Door_Motor_Config * motor_obj);
STD_ReturnType Door_Motor_Close(const Door_Motor_Config * motor_obj);
STD_ReturnType Door_Motor_Stop(const Door_Motor_Config * motor_obj);


#endif /* DOOR_MOTOR_H_ */