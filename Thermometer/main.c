/*
 * Thermometer.c
 *
 * Created: 2018-04-26 오후 11:31:39
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "DS18B20.h"
#include "128A_USART.h"

uint8_t buffer[8];
char msg[50] = {0,};
float degree;		

int main(void)
{	
	USART0_Init();
	
	if(!DS18B20_ReadROMCode(buffer, sizeof(buffer)))
	{
		sprintf(msg, "Read ROM Code: Error\r\n");
		USART0_TxBuffer((uint8_t*)msg, strlen(msg));
	}
	else
	{
		sprintf(msg, "Rom Code: [%02X][%02X][%02X][%02X][%02X][%02X][%02X][%02X]\r\n",
		buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7]);
		USART0_TxBuffer((uint8_t*)msg, strlen(msg));
	}
	
    /* Replace with your application code */
    while (1) 
    {
		if(!DS1B20_ReadTemp(&degree))
		{
			sprintf(msg, "Temp. Bytes: Error\r\n");
			USART0_TxBuffer((uint8_t*)msg, strlen(msg));
		}
		else
		{
			sprintf(msg, "Temp. Bytes: %3.2f\r\n", degree);
			USART0_TxBuffer((uint8_t*)msg, strlen(msg));
		}
		
		_delay_ms(1000);
    }
}
