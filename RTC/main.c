/*
 * DS1302.c
 *
 * Created: 2018-05-14 오전 8:08:56
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "128A_USART.h"
#include "DS1302.h"

_rtc rtc;

int main(void)
{
	char msg[30];
	
	USART0_Init();
	DS1302_Init();
	
	rtc.sec = 12;
	rtc.min = 12;
	rtc.hour = 12;
	rtc.wday = 1;
	rtc.day = 12;
	rtc.month = 12;
	rtc.year = 18;	
	
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "RTC Set Time...\r\n");
	USART0_TxBuffer((uint8_t*)msg, strlen(msg));
	
	DS1302_SetTime(&rtc);
	
    /* Replace with your application code */
    while (1) 
    {
		DS1302_GetTime(&rtc);
		
		memset(msg, 0, sizeof(msg));
		sprintf(msg, "%02u-%02u-%02u [%s] %02u:%02u:%02u\r\n", rtc.year, rtc.month, rtc.day, wday[rtc.wday], rtc.hour, rtc.min, rtc.sec);
		USART0_TxBuffer((uint8_t*)msg, strlen(msg));
		
		_delay_ms(1000);
    }
}

