/*
 * USART.h
 *
 * Created: 9/12/2024 9:56:38 PM
 *  Author: mo ali
 */ 
#include "../GPIO.h"

#ifndef USART_H_
#define USART_H_
#define BAUD 9600            // Baud rate for USART
#define MYUBRR F_CPU/16/BAUD-1  // Calculate UBRR value for the given baud rate


typedef struct{
	void (*interruptReceive)(void) ;
	Camera_status *computer_vision_cam ;
}USART_Config;

void USART_Init(USART_Config *usart_obj);
void USART_Trans(uint8 data);
void USART_SendStr(const uint8 *str);
#endif /* USART_H_ */