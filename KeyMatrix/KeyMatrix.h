/*
 * KeyMatrix.h
 *
 * Created: 2018-05-14 오후 2:26:13
 *  Author: kiki
 */ 


#ifndef KEYMATRIX_H_
#define KEYMATRIX_H_

#include <avr/io.h>

#define KM_DDR		DDRD
#define KM_PORT		PORTD
#define KM_PIN		PIND

#define KM_ROW1		PD0
#define KM_ROW2		PD1
#define KM_ROW3		PD2
#define KM_ROW4		PD3

#define KM_COL1		PD4
#define KM_COL2		PD5
#define KM_COL3		PD6
#define KM_COL4		PD7

void KM_ReadState();

extern uint8_t KM_State[16];

#endif /* KEYMATRIX_H_ */