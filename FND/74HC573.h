/*
 * _74HC573.h
 *
 * Created: 2018-04-17 오후 11:32:08
 *  Author: kiki
 */ 


#ifndef __74HC573_H_
#define __74HC573_H_

#include <avr/io.h>

#define LATCH_DDR	DDRF
#define LATCH_PORT	PORTF
#define LATCH_OUT1	PF1
#define LATCH_OUT2	PF2
#define LATCH_OUT3	PF3

#define DIG_DDR		DDRA
#define DIG_PORT	PORTA

#define SEG_DDR		DDRC
#define SEG_PORT	PORTC

#define DIGIT1		0x01
#define DIGIT2		0x02
#define DIGIT3		0x04
#define DIGIT4		0x08
#define DIGIT5		0x10
#define DIGIT6		0x20
#define DIGIT7		0x40
#define DIGIT8		0x80

void LATCH_Init(void);
void LATCH_On(uint8_t pins);
void LATCH_Off(uint8_t pins);
void LATCH_SetDigit(uint8_t value);
void LATCH_SetSegment(uint8_t value, uint8_t dot);

extern uint8_t FND_Numbers[10];
extern uint8_t FND_Chars[4];

#endif /* __74HC573_H_ */