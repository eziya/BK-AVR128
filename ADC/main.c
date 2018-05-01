/*
 * ADC.c
 *
 * Created: 2018-05-01 오후 8:59:04
 * Author : kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

int main(void)
{
	uint16_t adcVal;
	char buffer[30];
	
	USART0_Init();
	ADC_Init(0);
	
    /* Replace with your application code */
    while (1) 
    {
		adcVal = ADC_Read();
		
		sprintf(buffer, "%d\r\n", adcVal);		
		USART0_TxBuffer((uint8_t*)buffer, strlen(buffer));
		_delay_ms(1000);
    }
}

