/*
 * External_Interrupt.h
 *
 * Created: 9/8/2024 5:26:15 PM
 *  Author: mo ali
 */ 


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_
/*---------------Includes--------------*/
#include "Interrupt_CFG.h"
/*-------------Macro Declaration-----------*/

/*-------------Macro Functions----------------*/

// Define the Interrupt at Falling or Rising  or low level or at any change 
#define INT0_SENSE_CONTROL(x)				(MCUCR = (MCUCR & 0xFC) | (x & 0x03))
#define INT1_SENSE_CONTROL(x)				(MCUCR = (MCUCR & 0xF3) | (x & 0x0C))

// Enable & Disable INT0 and INT1
#define INT0_INTERRUPT_ENBALE()				(SET_BIN(GICR,6))
#define INT0_INTERRUPT_DISABLE()			(RESET_BIN(GICR,6))
#define INT1_INTERRUPT_ENBALE()				(SET_BIN(GICR,7))
#define INT1_INTERRUPT_DISABLE()			(RESET_BIN(GICR,7))

// Set & Clear INT0F and INT1F
#define INT0_SET_FLAG()						(SET_BIN(GIFR,6))
#define INT0_CLEAR_FLAG()					(RESET_BIN(GIFR,6))
#define INT1_SET_FLAG()						(SET_BIN(GIFR,7))
#define INT1_CLEAR_FLAG()					(RESET_BIN(GIFR,7))

// Enable Global Interrupt 
//#define GLOBAL_INTERRUPT_ENABLE()			(sei())





/*-------------Data Type-----------------------*/

//The MCU Control Register contains control bits for interrupt sense control and general MCU functions
typedef enum{
	INTx_LOW_LEVEL_INTERRUPT = 0 ,
	INTx_ANY_LOGIC_INTERRUP ,
	INTx_FALLING_EDGE_INTERRUPT ,
	INTx_RISING_EDGE_INTERRUPT
}INTx_Define_Change;

typedef enum{
	INT0_,
	INT1_
}INTx;

typedef struct {
	void (*InterruptManager)(void);
	INTx	intx;					// select the interrupt pin (INT0 , INT1)
	INTx_Define_Change con_reg;		//Control Register contains control bits for interrupt sense control and general MCU functions
}INTx_CONFG;

/*--------------------Functions--------------------*/
STD_ReturnType INTx_Initialize(const INTx_CONFG* _int);
STD_ReturnType INTx_DeInitialize(const INTx_CONFG* _int);


#endif /* EXTERNAL_INTERRUPT_H_ */