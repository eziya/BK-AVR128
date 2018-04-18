/*
 * _74HC573.c
 *
 * Created: 2018-04-17 오후 11:32:22
 *  Author: kiki
 */ 
#include "../Common.h"
#include "74HC573.h"

uint8_t FND_Numbers[10] = {
	0xC0,		/* 0 */
	0xF9,		/* 1 */
	0xA4,
	0xB0,
	0x99,
	0x92,
	0x82,
	0xF8,
	0x80,
	0x90		/* 9 */
};

uint8_t FND_Chars[4] = {
	0b10001100,
	0b11000111,
	0b10001000,
	0b10010001	
};

void LATCH_Init()
{
	LATCH_DDR |= _BV(LATCH_OUT1) | _BV(LATCH_OUT2) | _BV(LATCH_OUT3);
	SEG_DDR = 0xFF;
	DIG_DDR = 0xFF;
}

void LATCH_On(uint8_t pins)
{
	LATCH_PORT |= pins;
}

void LATCH_Off(uint8_t pins)
{
	LATCH_PORT &= ~pins;	
}

void LATCH_SetDigit(uint8_t value)
{
	DIG_PORT = value;	
}

void LATCH_SetSegment(uint8_t value, bool dot)
{
	if(dot) value &= ~0x80;
	SEG_PORT = value;
}