/*
 * PWM_LED.h
 *
 * Created: 2018-04-16 오후 2:46:42
 *  Author: kiki
 */ 


#ifndef PWM_LED_H_
#define PWM_LED_H_

#include <avr/io.h>

void LED_Init();
void LED_SetDuty(uint8_t duty);

#endif /* PWM_LED_H_ */