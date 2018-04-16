/*
 * PWM_LED.c
 *
 * Created: 2018-04-16 오후 2:46:52
 *  Author: kiki
 */ 

#include "PWM_LED.h"

void LED_Init()
{
	DDRB |= _BV(PB4);					//Configure OC0 pin as output
	TCCR0 |= _BV(WGM01) | _BV(WGM00);	//Fast PWM
	TCCR0 |= _BV(COM01) | _BV(COM00);	//Inverting mode: Low => High
	TCCR0 |= _BV(CS02) | _BV(CS01);		//Prescaler 256, 8
}

void LED_SetDuty(uint8_t duty)
{	
	OCR0 = duty;
}