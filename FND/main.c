/*
 * FND.c
 *
 * Created: 2018-04-26 오후 11:19:55
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "74HC573.h"

static void TestFND();

int main(void)
{
	TestFND();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

static void TestFND()
{
	LATCH_Init();
	LATCH_On(_BV(LATCH_OUT1) | _BV(LATCH_OUT2));
	
	for(int i = 0; i < 10000; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			/* Display numbers */
			int val = i;
			
			LATCH_SetDigit(DIGIT8);
			LATCH_SetSegment(FND_Numbers[val%10], 0);
			_delay_ms(1);
			
			val = val / 10;
			
			LATCH_SetDigit(DIGIT7);
			LATCH_SetSegment(FND_Numbers[val%10], 0);
			_delay_ms(1);
			
			val = val / 10;
			
			LATCH_SetDigit(DIGIT6);
			LATCH_SetSegment(FND_Numbers[val%10],  0);
			_delay_ms(1);
			
			val = val / 10;
			
			LATCH_SetDigit(DIGIT5);
			LATCH_SetSegment(FND_Numbers[val%10], 0);
			_delay_ms(1);
			
			/* Display characters */
			LATCH_SetDigit(DIGIT1);
			LATCH_SetSegment(FND_Chars[0], 0);
			_delay_ms(1);
			
			LATCH_SetDigit(DIGIT2);
			LATCH_SetSegment(FND_Chars[1], 0);
			_delay_ms(1);
			
			LATCH_SetDigit(DIGIT3);
			LATCH_SetSegment(FND_Chars[2], 0);
			_delay_ms(1);
			
			LATCH_SetDigit(DIGIT4);
			LATCH_SetSegment(FND_Chars[3], 0);
			_delay_ms(1);
		}
	}
	
	LATCH_Off(_BV(LATCH_OUT1) | _BV(LATCH_OUT2));
}
