/*
 * USART.c
 *
 * Created: 2018-04-26 오후 11:18:37
 * Author : kiki
 */ 

#include <avr/io.h>
#include <stdbool.h>

#include "128A_USART.h"

int main(void)
{
	USART0_Init();
	
    /* Replace with your application code */
    while (1) 
    {
		uint8_t data;
		if(USART0_RxByte(&data))
		{
			USART0_TxByte(data);			
		}		
    }
}

