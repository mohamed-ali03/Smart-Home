/*
 * USART.c
 *
 * Created: 9/12/2024 9:56:23 PM
 *  Author: mo ali
 */ 
#include "USART.h"

void (*interruptHandler) (void);
Camera_status *flag ;
// Initialize the USART with the specified baud rate and frame format (8 data bits, 1 stop bit)
void USART_Init(USART_Config *usart_obj){
	// Set baud rate
	uint32 ubrr_value = MYUBRR;
	UBRRH = (uint8)(ubrr_value >> 8);   // High byte
	UBRRL = (uint8)ubrr_value;          // Low byte

	// Enable transmitter and Reciever and interrupt (TXEN) in UCSRB
	UCSRB = (1 << TXEN) | ( 1 << RXEN)| (1 << RXCIE);

	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	
	// call back funciton 
	interruptHandler = usart_obj->interruptReceive ;
	
	// keypad flag 
	flag = usart_obj->computer_vision_cam ;
	sei();
}

// Function to send a single character via USART
void USART_Trans(uint8 data) {
	// Wait until the transmit buffer is empty (UDRE flag is set)
	while (!(UCSRA & (1 << UDRE)));
	
	// Put the data into the USART data register (UDR), which sends the data
	UDR = data;
}

// Function to send a string via USART
void USART_SendStr(const uint8 *str) {
	// Loop through the string until the null terminator is reached
	while (*str) {
		USART_Trans(*str++);  // Transmit each character
	}
}

uint8 USART_Receive(void) {
	// Wait for data to be received (RXC flag set)
	while (!(UCSRA & (1 << RXC)));

	// Get and return received data from buffer
	return UDR;
}

ISR(USART_RXC_vect){
	uint8 receive = UDR ;
	if (receive == '0'){
		*flag = No_one;
	}
	else if(receive == '1') {
		*flag = Face_Detected ;
	}
	else if (receive == '2' ){
		*flag = Face_Not_Detected ;
	}
	
	if(interruptHandler){
		interruptHandler();
	}
}