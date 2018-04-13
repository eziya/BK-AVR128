/*
 * Buzzer.h
 *
 * Created: 2018-04-10 오후 10:12:37
 *  Author: kiki
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>
#include <util/delay.h>

#define PWM_DDR		DDRE
#define PWM_PORT	PORTE
#define PWM_OUT		PE7

void GPIO_MakeSound(float freq, uint8_t duty, uint16_t ms);

#endif /* BUZZER_H_ */