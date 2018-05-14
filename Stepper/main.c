/*
 * Stepper.c
 *
 * Created: 2018-05-09 오후 10:01:03
 * Author : kiki
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "Stepper.h"

uint16_t cnt = 0;
int main(void)
{
	STEPPER_Init();
	
	/* 1-Phase Full Step */		
	STEPPER_Rotate(STEPPER_WAVEDRIVE, 1, 128);
	STEPPER_Rotate(STEPPER_WAVEDRIVE, 0, 128);		
	
	/* 2-Phase Full Step */	
	STEPPER_Rotate(STEPPER_FULLSTEP, 1, 128);		
	STEPPER_Rotate(STEPPER_FULLSTEP, 0, 128);		
	
	/* 2-Phase Half Step */	
	STEPPER_Rotate(STEPPER_HALFSTEP, 1, 128);
	STEPPER_Rotate(STEPPER_HALFSTEP, 0, 128);		
		
    /* Replace with your application code */
    while (1) 
    {
		
    }
}

