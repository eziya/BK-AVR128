/*
 * _128A_ADC.c
 *
 * Created: 2018-05-01 오후 8:59:43
 *  Author: kiki
 */ 

#include "128A_ADC.h"

void ADC_Init(uint8_t channel)
{
	/* Configure reference voltage */
	ADMUX |= _BV(REFS0);
	
	/* Configure channel */
	ADMUX |= ((ADMUX & 0xE0) | channel);
	
	/* Prescaler 128 */
	ADCSRA |= (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0));
	
	/* Auto Trigger Mode (Free Running) */
	ADCSRA |= _BV(ADFR);
	
	/* Enable ADC */
	ADCSRA |= _BV(ADEN);
	
	/* Start ADC */
	ADCSRA |= _BV(ADSC);
}

uint16_t ADC_Read()
{
	while(!(ADCSRA & _BV(ADIF)));
	return ADC;
}