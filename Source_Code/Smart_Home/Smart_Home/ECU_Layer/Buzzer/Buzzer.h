/*
 * Buzzer.h
 *
 * Created: 9/11/2024 7:33:18 PM
 *  Author: mo ali
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
#include "../../MCAL_LAYER/GPIO.h"

typedef struct {
	GPIO_PIN_CONFIG buzzer;
}Buzzer_Config;


STD_ReturnType Buzzer_INIT(const Buzzer_Config *Buzzer_obj);
STD_ReturnType Buzzer_Play(const Buzzer_Config *Buzzer_obj);
STD_ReturnType Buzzer_Stop(const Buzzer_Config *Buzzer_obj);



#endif /* BUZZER_H_ */