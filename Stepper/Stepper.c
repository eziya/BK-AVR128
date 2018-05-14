/*
 * Stepper.c
 *
 * Created: 2018-05-09 오후 10:01:45
 *  Author: kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <util/delay.h>
#include "Stepper.h"

static void STEPPER_WaveDrive(uint8_t clockwise, uint16_t steps);
static void STEPPER_FullStep(uint8_t clockwise, uint16_t steps);
static void STEPPER_HalfStep(uint8_t clockwise, uint16_t steps);

/* 0b0000[A1][B1][A2][B2] */
static uint8_t wave_pattern[4] = {0x08,0x04,0x02,0x01};
static uint8_t full_pattern[4] = {0x0C,0x06,0x03,0x09};	
static uint8_t half_pattern[8] = {0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09};

void STEPPER_Init(void)
{
	STEPPER_DDR = _BV(STEPPER_ORANGE) | _BV(STEPPER_YELLOW) | _BV(STEPPER_PINK) | _BV(STEPPER_BLUE);	
}

void STEPPER_Rotate(uint8_t method, uint8_t clockwise, uint16_t steps)
{
	if(method == STEPPER_WAVEDRIVE)
	{
		STEPPER_WaveDrive(clockwise, steps);
	}
	else if(method == STEPPER_FULLSTEP)
	{
		STEPPER_FullStep(clockwise, steps);
	}
	else if(method == STEPPER_HALFSTEP)
	{
		STEPPER_HalfStep(clockwise, steps);
	}	
}

static void STEPPER_WaveDrive(uint8_t clockwise, uint16_t steps)
{
	if(clockwise)
	{
		for(int i=0; i < steps; i++)
		{
			for(int j=0; j < 4; j++)
			{
				STEPPER_PORT = 0;
				if(wave_pattern[j%4] & 0x08) STEPPER_PORT |= _BV(STEPPER_PINK);				
				if(wave_pattern[j%4] & 0x04) STEPPER_PORT |= _BV(STEPPER_YELLOW);				
				if(wave_pattern[j%4] & 0x02) STEPPER_PORT |= _BV(STEPPER_ORANGE);				
				if(wave_pattern[j%4] & 0x01) STEPPER_PORT |= _BV(STEPPER_BLUE);				
				_delay_ms(STEPPER_DELAY);
			}
		}		
	}
	else
	{
		for(int i=0; i < steps; i++)
		{
			for(int j=3; j >= 0; j--)
			{
				STEPPER_PORT = 0;
				if(wave_pattern[j%4] & 0x08) STEPPER_PORT |= _BV(STEPPER_PINK);				
				if(wave_pattern[j%4] & 0x04) STEPPER_PORT |= _BV(STEPPER_YELLOW);				
				if(wave_pattern[j%4] & 0x02) STEPPER_PORT |= _BV(STEPPER_ORANGE);				
				if(wave_pattern[j%4] & 0x01) STEPPER_PORT |= _BV(STEPPER_BLUE);
				_delay_ms(STEPPER_DELAY);								
			}
		}
	}
}

static void STEPPER_FullStep(uint8_t clockwise, uint16_t steps)
{
	if(clockwise)
	{
		for(int i=0; i < steps; i++)
		{
			for(int j=0; j < 4; j++)
			{
				STEPPER_PORT = 0;
				if(full_pattern[j%4] & 0x08) STEPPER_PORT |= _BV(STEPPER_PINK);				
				if(full_pattern[j%4] & 0x04) STEPPER_PORT |= _BV(STEPPER_YELLOW);				
				if(full_pattern[j%4] & 0x02) STEPPER_PORT |= _BV(STEPPER_ORANGE);				
				if(full_pattern[j%4] & 0x01) STEPPER_PORT |= _BV(STEPPER_BLUE);				
				_delay_ms(STEPPER_DELAY);
			}
		}		
	}
	else
	{
		for(int i=0; i < steps; i++)
		{
			for(int j=3; j >= 0; j--)
			{
				STEPPER_PORT = 0;
				if(full_pattern[j%4] & 0x08) STEPPER_PORT |= _BV(STEPPER_PINK);				
				if(full_pattern[j%4] & 0x04) STEPPER_PORT |= _BV(STEPPER_YELLOW);				
				if(full_pattern[j%4] & 0x02) STEPPER_PORT |= _BV(STEPPER_ORANGE);				
				if(full_pattern[j%4] & 0x01) STEPPER_PORT |= _BV(STEPPER_BLUE);
				_delay_ms(STEPPER_DELAY);								
			}
		}
	}
}

static void STEPPER_HalfStep(uint8_t clockwise, uint16_t steps)
{
	if(clockwise)
	{
		for(int i=0; i < steps; i++)
		{
			for(int j=0; j < 8; j++)
			{
				STEPPER_PORT = 0;
				if(half_pattern[j%8] & 0x08) STEPPER_PORT |= _BV(STEPPER_PINK);				
				if(half_pattern[j%8] & 0x04) STEPPER_PORT |= _BV(STEPPER_YELLOW);				
				if(half_pattern[j%8] & 0x02) STEPPER_PORT |= _BV(STEPPER_ORANGE);				
				if(half_pattern[j%8] & 0x01) STEPPER_PORT |= _BV(STEPPER_BLUE);				
				_delay_ms(STEPPER_DELAY);
			}
		}		
	}
	else
	{
		for(int i=0; i < steps; i++)
		{
			for(int j=7; j >= 0; j--)
			{
				STEPPER_PORT = 0;
				if(half_pattern[j%8] & 0x08) STEPPER_PORT |= _BV(STEPPER_PINK);				
				if(half_pattern[j%8] & 0x04) STEPPER_PORT |= _BV(STEPPER_YELLOW);				
				if(half_pattern[j%8] & 0x02) STEPPER_PORT |= _BV(STEPPER_ORANGE);				
				if(half_pattern[j%8] & 0x01) STEPPER_PORT |= _BV(STEPPER_BLUE);
				_delay_ms(STEPPER_DELAY);								
			}
		}
	}
}