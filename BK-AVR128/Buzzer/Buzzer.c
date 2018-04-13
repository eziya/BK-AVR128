/*
 * Buzzer.c
 *
 * Created: 2018-04-10 오후 10:12:51
 *  Author: kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include "Buzzer.h"

void GPIO_MakeSound(float freq, uint8_t duty, uint16_t ms)
{
	/* Output configuration */
	PWM_DDR |= _BV(PWM_OUT);
	PWM_PORT &= ~_BV(PWM_OUT);
	
	/* T = 1 / f, e.g. 1/8000Hz = 125us */
	uint16_t usPeriod = 1 / freq * 1000000;
	
	/* duty cycle = period * duty / 100 */
	uint16_t usHighPeriod = usPeriod * duty / 100;
	uint16_t usLowPeriod = usPeriod - usHighPeriod;
	
	/* frequency times pulse = 1 sec */
	for(int i = 0; i < freq * ms / 1000; i++)
	{
		PWM_PORT |= _BV(PWM_OUT);
		for(int j=0; j < usHighPeriod; j++) _delay_us(1);
		PWM_PORT &= ~_BV(PWM_OUT);
		for(int j=0; j < usLowPeriod; j++) _delay_us(1);
	}
}
