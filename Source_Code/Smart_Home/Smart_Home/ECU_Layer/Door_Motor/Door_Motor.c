/*
 * CFile1.c
 *
 * Created: 9/10/2024 7:25:42 PM
 *  Author: mo ali
 */

#include "Door_Motor.h"

STD_ReturnType Door_Motor_Init(const Door_Motor_Config * motor_obj){
	STD_ReturnType status = RET_OK;
	if (NULL == motor_obj){
		status = RET_NOT_OK;
	}
	else
	{
		DDRD |= (1 << BIT4) | (1 << BIT5);
	}
	return status ;
}

STD_ReturnType Door_Motor_Open(const Door_Motor_Config * motor_obj){
	STD_ReturnType status = RET_OK;
	if (NULL == motor_obj){
		status = RET_NOT_OK;
	}
	else
	{
		PORTD |= (1 << BIT4);
		PORTD &= ~(1 << BIT5);
	}
	return status ;
}

STD_ReturnType Door_Motor_Close(const Door_Motor_Config * motor_obj){
	STD_ReturnType status = RET_OK;
	if (NULL == motor_obj){
		status = RET_NOT_OK;
	}
	else
	{
		PORTD &= ~(1 << BIT4);
		PORTD |= (1 << BIT5);
	}
	return status ; 
}

STD_ReturnType Door_Motor_Stop(const Door_Motor_Config * motor_obj){
	STD_ReturnType status = RET_OK;
	if (NULL == motor_obj){
		status = RET_NOT_OK;
	}
	else
	{
		PORTD &= ~(1 << BIT4);
		PORTD &= ~(1 << BIT5);
	}
	return status ;
}
