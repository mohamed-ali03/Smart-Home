/*
 * USART.c
 *
 * Created: 9/12/2024 9:56:23 PM
 *  Author: mo ali
 */ 
#include "USART.h"
// Initialize the USART with the specified baud rate and frame format (8 data bits, 1 stop bit)
void USART_Init(void) {
	// Set baud rate
	unsigned int ubrr_value = MYUBRR;
	UBRRH = (unsigned char)(ubrr_value >> 8);   // High byte
	UBRRL = (unsigned char)ubrr_value;          // Low byte

	// Enable transmitter (TXEN) in UCSRB
	UCSRB = (1 << TXEN) | ( 1 << RXEN);

	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

// Function to send a single character via USART
void USART_Trans(char data) {
	// Wait until the transmit buffer is empty (UDRE flag is set)
	while (!(UCSRA & (1 << UDRE)));
	
	// Put the data into the USART data register (UDR), which sends the data
	UDR = data;
}

// Function to send a string via USART
void USART_SendStr(const char* str) {
	// Loop through the string until the null terminator is reached
	while (*str) {
		USART_Trans(*str++);  // Transmit each character
	}
}
