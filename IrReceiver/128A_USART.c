/*
 * _128A_USART.c
 *
 * Created: 2018-04-14 오전 8:39:08
 *  Author: kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include "128A_USART.h"

void USART0_Init()
{
	/* 2배속 모드 */
	UCSR0A |= _BV(U2X0);
		
	/* Baud rate 설정, UBRR = (fosc / (8 * BAUD)) - 1 */
	/* 8MHz / 8 / 9600 - 1 = 103 */
	uint16_t baudrate = F_CPU / 8 / USART0_BAUDRATE - 1;
	UBRR0H = (baudrate >> 8) & 0xFF;
	UBRR0L = baudrate & 0xFF;
	
	/* 비동기, 8-N-1 설정 */
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
	
	/* 송수신 Enable */
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
}

bool USART0_RxByte(uint8_t *data)
{
	uint16_t loop = USART0_TIMEOUT;
	do
	{
		if(UCSR0A & _BV(RXC0))
		{
			*data = UDR0;
			return true;
		}
	} while (--loop);
	
	return false;
}

void USART0_TxByte(uint8_t data)
{
	while((UCSR0A & _BV(UDRE0)) == 0);
	UDR0 = data;
}

bool USART0_RxBuffer(uint8_t *buffer, uint16_t len)
{
	for(int i=0; i < len; i++)
	{
		if(!USART0_RxByte(&buffer[i]))
		{
			return false;
		}
	}
	
	return true;
}

void USART0_TxBuffer(uint8_t *buffer, uint16_t len)
{
	for(int i=0; i < len; i++)
	{
		USART0_TxByte(buffer[i]);
	}
}