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



void USART_Init(void);
void USART_Trans(char data);
void USART_SendStr(const char* str);
#endif /* USART_H_ */