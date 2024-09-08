/*
 * Interrupt_CFG.h
 *
 * Created: 9/8/2024 5:31:45 PM
 *  Author: mo ali
 */ 


#ifndef INTERRUPT_CFG_H_
#define INTERRUPT_CFG_H_

/*------------------Includes---------------------*/
#include "../GPIO.h"
/*------------------Macro Declaration------------*/
#define INTERRUPT_ENABLE            1
#define INTERRUPT_DISABLE           0
#define INTERRUPT_OCCUR             1
#define INTERRUPT_NOT_OCCUR         0
#define INTERRUPT_PRIORITY_ENABLE   1
#define INTERRUPT_PRIORITY_DISABLE  0
/*------------------Macro Function Declaration---------------------*/


/*------------------Data Type Declaration--------*/
typedef enum {
	INTERRUPT_LOW_PRIORITY = 0 ,
	INTERRUPT_HIGH_PRIORITY
}INTERRUPT_INTERRUPT_PRIORITY;

#endif /* INTERRUPT_CFG_H_ */