/*
 * _128A_ADC.h
 *
 * Created: 2018-05-01 오후 8:59:30
 *  Author: kiki
 */ 


#ifndef __128A_ADC_H_
#define __128A_ADC_H_

#include <avr/io.h>

void ADC_Init(uint8_t channel);
uint16_t ADC_Read(void);

#endif /* __128A_ADC_H_ */