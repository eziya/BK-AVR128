/*
 * main.c
 *
 * Created: 2018-05-14 오후 2:25:27
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "KeyMatrix.h"

int main(void)
{
	/* Eable LATCH */
	DDRF |= _BV(PF3);
	PORTF |= _BV(PF3);
	
	/* Eanble LED */
	DDRA = 0xFF;	
	PORTA = 0xFF;
	
    /* Replace with your application code */
    while (1) 
    {
		KM_ReadState();
		
		if(KM_State[0])	PORTA &= ~_BV(PA0);
		else PORTA |= _BV(PA0);
		
		if(KM_State[1])	PORTA &= ~_BV(PA1);
		else PORTA |= _BV(PA1);
		
		if(KM_State[2])	PORTA &= ~_BV(PA2);
		else PORTA |= _BV(PA2);
		
		if(KM_State[3])	PORTA &= ~_BV(PA3);
		else PORTA |= _BV(PA3);
		
		if(KM_State[4])	PORTA &= ~_BV(PA4);
		else PORTA |= _BV(PA4);
		
		if(KM_State[5])	PORTA &= ~_BV(PA5);
		else PORTA |= _BV(PA5);
		
		if(KM_State[6])	PORTA &= ~_BV(PA6);
		else PORTA |= _BV(PA6);
		
		if(KM_State[7])	PORTA &= ~_BV(PA7);
		else PORTA |= _BV(PA7);
    }
}
