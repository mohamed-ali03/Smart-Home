/*
 * External_Interrupt.c
 *
 * Created: 9/8/2024 5:25:50 PM
 *  Author: mo ali
 */ 

#include "External_Interrupt.h"

/*-----------------------------Call Back Functions-------------------------------------*/
static void(*INT0_InterruptHandler)(void);
static void(*INT1_InterruptHandler)(void);

/*-------------------------------------Asisstant Function Declaration--------------------------------------*/
static void INT0_Init(const INTx_CONFG* _int);
static void INT1_Init(const INTx_CONFG* _int);
static void INT0_DEInit(const INTx_CONFG* _int);
static void INT1_DEInit(const INTx_CONFG* _int);

STD_ReturnType INTx_Initialize(const INTx_CONFG* _int){
	STD_ReturnType status = RET_OK ;
	if (NULL == _int){
		status = RET_NOT_OK ;
	}
	else {
		if(_int->intx == INT0_){
			INT0_Init(_int);
		}
		else if (_int->intx == INT1_){
			INT1_Init(_int);
		}
		else{
			/*nothing*/
		}
		sei();
	}
	return status ;
}

STD_ReturnType INTx_DeInitialize(const INTx_CONFG* _int){
	STD_ReturnType status = RET_OK ;
	if (NULL == _int){
		status = RET_NOT_OK ;
	}
	else {
		if(_int->intx == INT0_){
			INT0_DEInit(_int);
		}
		else if (_int->intx == INT1_){
			INT1_DEInit(_int);
		}
		else{
			/*nothing*/
		}
	}
	return status ;
}



/*----------------------------------------Asisstant Functoins--------------------------------------------*/
static void INT0_Init(const INTx_CONFG* _int){
	// Disable Interrupt 0
	INT0_INTERRUPT_DISABLE();
	// Configure pin PD2 as input pin 
	RESET_BIN(DDRD,PIND2);
	// Configure Interrupt 0 Sense Control
	INT0_SENSE_CONTROL(_int->con_reg);
	// assign the call back Pointer 
	INT0_InterruptHandler = _int->InterruptManager;
	// Enable Interrupt 0
	INT0_INTERRUPT_ENBALE();
}

static void INT0_DEInit(const INTx_CONFG* _int){
	// Disable Interrupt 0
	INT0_INTERRUPT_DISABLE();
}


static void INT1_Init(const INTx_CONFG* _int){
	// Disable Interrupt 1
	INT1_INTERRUPT_DISABLE();
	// Configure pin PD3 as input pin
	RESET_BIN(DDRD,PIND3);
	// Configure Interrupt 1 Sense Control
	INT1_SENSE_CONTROL(_int->con_reg);
	// assign the call back Pointer
	INT1_InterruptHandler = _int->InterruptManager;
	// Enable Interrupt 1
	INT1_INTERRUPT_ENBALE();
}

static void INT1_DEInit(const INTx_CONFG* _int){
	// Disable Interrupt 1
	INT1_INTERRUPT_DISABLE();
}


/*-------------------------------------ISR Function-----------------------------------------*/
ISR(INT0_vect){
	INT0_CLEAR_FLAG();
	
	if(INT0_InterruptHandler){
		INT0_InterruptHandler();
	}
}

ISR(INT1_vect){
	INT1_CLEAR_FLAG();
	
	if(INT1_InterruptHandler){
		INT1_InterruptHandler();
	}
}

