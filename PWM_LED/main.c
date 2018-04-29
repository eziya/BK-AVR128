/*
 * PWM_LED.c
 *
 * Created: 2018-04-26 오후 11:23:25
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "PWM_LED.h"

static void TestPWMLED();

int main(void)
{
	TestPWMLED();
    /* Replace with your application code */
    while (1) 
    {
    }
}

static void TestPWMLED()
{
	LED_Init();
	
	while(1)
	{
		for(int i=0; i < 256; i++)
		{
			LED_SetDuty(i);
			_delay_ms(10);
		}
	}
}