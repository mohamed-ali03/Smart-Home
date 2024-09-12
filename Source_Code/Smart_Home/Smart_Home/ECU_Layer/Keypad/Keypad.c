/*
 * CFile1.c
 *
 * Created: 9/11/2024 2:10:27 PM
 *  Author: mo ali
 */ 

#include "Keypad.h"

static STD_ReturnType Keypad_Get_char(const Keypad_Config *keypad_obj,uint8 *_char,bool *Door_Flag) ;

const uint8 keypad[4][3] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'},
	{'*', '0', '#'}
};

STD_ReturnType Keypad_Init(Keypad_Config *keypad_obj,uint8 *password){
	STD_ReturnType status = RET_OK;
	uint32 count ;
	if (NULL == keypad_obj){
		status = RET_NOT_OK;
	}
	else{
		// init Rows 
		for (count = 0 ; count <4 ; count++){
			status = GPIO_PIN_Initialize(&(keypad_obj->Rows[count]));
		}
		// ini Columns 
		for(count = 0 ; count < 3 ; count++){
			status = GPIO_PIN_Initialize(&(keypad_obj->Columns[count]));
		}
		// init password
		keypad_obj->ActualPassword = password;
	}
	return status;
}



STD_ReturnType Keypad_Get_Check_Password(const Keypad_Config *keypad_obj,uint8 pass[],bool *ispasstrue,bool *Door_Flag){
	STD_ReturnType status = RET_OK;
	uint8 key ;
	uint32 index = 0 ;
	uint32 attempt = 0 ;
	if (NULL == keypad_obj || NULL == pass){
		status = RET_NOT_OK;
	}
	else{
		while(attempt < 1 ){
			if(*Door_Flag){
				break;
			}
			status = Keypad_Get_char(keypad_obj,&key,Door_Flag);
			if(key == '#'){
				if (strcmp(pass,keypad_obj->ActualPassword) == 0 ){
					*ispasstrue = True;
					break;
				}
				else {
					*ispasstrue = False;
					if(index==4)
						attempt++;
				}
				index = 0;
			}
			else if (index <4){
				pass[index] = key ;
				index++;
			}
		}
	}
	return status;
}



/*-----------------------------------------------------asissstant functions---------------------------------------*/
static STD_ReturnType Keypad_Get_char(const Keypad_Config *keypad_obj,uint8 *_char,bool *Door_Flag){
	STD_ReturnType status = RET_OK;
	bool flag = 0 ;
	GPIO_PIN_LOGIC logic ;
	
	uint32 clear ;
	uint32 count_rows ;
	uint32 count_colums;
	
	if (NULL == keypad_obj ){
		status = RET_NOT_OK;
	}
	else{
		while(1){
			if(flag || *Door_Flag){
				break;
			}
			for(count_colums = 0 ; count_colums < 3 ; count_colums++)
			{
				if (flag){
					break;
				}
				// set all columns low then set the required column high
				for(clear = 0 ; clear < 3 ; clear++){
					status = GPIO_PIN_Write_logic(&(keypad_obj->Columns[clear]),GPIO_PIN_LOGIC_HIGH);
				}
				status = GPIO_PIN_Write_logic(&(keypad_obj->Columns[count_colums]),GPIO_PIN_LOGIC_LOW);
				
				for(count_rows = 0 ; count_rows < 4 ; count_rows++){
					status = GPIO_PIN_Read_Logic(&(keypad_obj->Rows[count_rows]),&logic);
					
					if (logic == GPIO_PIN_LOGIC_LOW){
						while(1){
							status = GPIO_PIN_Read_Logic(&(keypad_obj->Rows[count_rows]),&logic);
							if(logic == GPIO_PIN_LOGIC_HIGH){
								break;
							}
						}
						*_char = keypad[count_rows][count_colums];
						flag = True ;
						break;
					}
				}
			}
		}
	}
	
	return status;
}