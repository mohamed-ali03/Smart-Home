/*
 * STD_DataType.h
 *
 * Created: 9/7/2024 11:06:59 PM
 *  Author: mo ali
 */ 


#ifndef STD_DATATYPE_H_
#define STD_DATATYPE_H_
/***************************INCLUDES****************************/
#include "STD_Library.h"
/***************************MACRO DECLERATION ****************************/
#define F_CPU 8000000UL      // CPU frequency set to 8 MHz


#define  uint8      unsigned char
#define  uint16     unsigned short
#define  uint32     unsigned int
#define  sint8      signed char
#define  sint16     signed short
#define  sint32     signed int

#define ENABLE         0x01
#define DISABLE        0x00
#define STD_ReturnType      uint8

#define RET_NOT_OK          0x00
#define RET_OK              0x01
/***************************MACRO FUNCTION****************************/


/***************************DATA TYPE****************************/

typedef enum {
	BIT0 ,
	BIT1 ,
	BIT2 ,
	BIT3 ,
	BIT4 ,
	BIT5 ,
	BIT6 ,
	BIT7 ,
}BITx_;

typedef enum{
	False , 
	True
}bool;


typedef enum {
	No_one,
	Face_Detected,
	Face_Not_Detected,
}Camera_status;

/***************************FUNCTIONS****************************/




#endif /* STD_DATATYPE_H_ */