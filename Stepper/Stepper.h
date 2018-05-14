/*
 * Stepper.h
 *
 * Created: 2018-05-09 오후 10:01:34
 *  Author: kiki
 */ 

#ifndef STEPPER_H_
#define STEPPER_H_

#include <avr/io.h>

#define STEPPER_DDR		DDRB
#define STEPPER_PORT	PORTB
#define STEPPER_PIN		PINB

#define STEPPER_ORANGE	PB0
#define STEPPER_YELLOW	PB1
#define STEPPER_PINK	PB2
#define STEPPER_BLUE	PB3

#define STEPPER_WAVEDRIVE	1
#define STEPPER_FULLSTEP	2
#define STEPPER_HALFSTEP	3

#define STEPPER_DELAY		2

void STEPPER_Init(void);
void STEPPER_Rotate(uint8_t method, uint8_t clockwise, uint16_t steps);

#endif /* STEPPER_H_ */