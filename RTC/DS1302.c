/*
 * DS1302.c
 *
 * Created: 2018-05-14 오전 8:09:56
 *  Author: kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <util/delay.h>
#include "DS1302.h"

static uint8_t DS1302_RxByte();
static void	DS1302_TxByte(uint8_t data);

static uint8_t DS1302_RxReg(uint8_t addr);
static void DS1302_TxReg(uint8_t addr, uint8_t data);

static void DS1302_RxBurst(uint8_t *data);
static void DS1302_TxBurst(uint8_t *data);

static uint8_t B2D(uint8_t bcd);
static uint8_t D2B(uint8_t decimal);

char *wday[8] = {"NA","SUN","MON","TUE","WED","THR","FRI","SAT"};

void DS1302_Init(void)
{
	/* Output SCLK, CE */
	DS1302_DDR |= _BV(DS1302_SCLK) | _BV(DS1302_CE);
}

static uint8_t	DS1302_RxByte()
{
	uint8_t value = 0;
	uint8_t currentBit = 0;
	
	/* Input IO */
	DS1302_DDR &= ~_BV(DS1302_IO);
	
	/* LSB first */
	for(int i=0; i < 8; i++)
	{
		currentBit = (DS1302_PIN & _BV(DS1302_IO)) ? 0x01 : 0x00;
		value |= (currentBit << i);
		
		/* Pulse SCLK */
		DS1302_PORT |= _BV(DS1302_SCLK);
		_delay_ms(1);
		DS1302_PORT &= ~_BV(DS1302_SCLK);		
	}	
	
	return value;
}

static void	DS1302_TxByte(uint8_t data)
{	
	/* Output IO */
	DS1302_DDR |= _BV(DS1302_IO);
	
	/* LSB first */
	for(int i=0; i < 8; i++)
	{
		if((data >> i) & 0x01)
		{
			DS1302_PORT |= _BV(DS1302_IO);
		}
		else
		{
			DS1302_PORT &= ~_BV(DS1302_IO);			
		}		
		
		/* Pulse SCLK */
		DS1302_PORT |= _BV(DS1302_SCLK);
		_delay_ms(1);
		DS1302_PORT &= ~_BV(DS1302_SCLK);
	}	
}

uint8_t DS1302_RxReg(uint8_t addr)
{
	uint8_t rxVal;
	
	uint8_t cmdByte = 0x81;
	cmdByte |= (addr << 1);
	
	DS1302_PORT &= ~_BV(DS1302_SCLK);
	DS1302_PORT |= _BV(DS1302_CE);
	
	DS1302_TxByte(cmdByte);
	rxVal = DS1302_RxByte();
	
	DS1302_PORT &= ~_BV(DS1302_CE);
	
	return rxVal;	
}

void DS1302_TxReg(uint8_t addr, uint8_t data)
{
	uint8_t cmdByte = 0x80;
	cmdByte |= 	(addr << 1);
	
	DS1302_PORT &= ~_BV(DS1302_SCLK);
	DS1302_PORT |= _BV(DS1302_CE);
	
	DS1302_TxByte(cmdByte);
	DS1302_TxByte(data);
	
	DS1302_PORT &= ~_BV(DS1302_CE);
}

void DS1302_RxBurst(uint8_t *data)
{
	uint8_t cmdByte = 0xBF;
		
	DS1302_PORT &= ~_BV(DS1302_SCLK);
	DS1302_PORT |= _BV(DS1302_CE);
	
	DS1302_TxByte(cmdByte);
	for(int i = 0; i < 8; i++)
	{
		data[i] = DS1302_RxByte();
	}
	
	DS1302_PORT &= ~_BV(DS1302_CE);			
}

void DS1302_TxBurst(uint8_t *data)
{
	uint8_t cmdByte = 0xBE;
	
	DS1302_PORT &= ~_BV(DS1302_SCLK);
	DS1302_PORT |= _BV(DS1302_CE);
	
	DS1302_TxByte(cmdByte);
	for(int i = 0; i < 8; i++)
	{
		DS1302_TxByte(data[i]);
	}
	
	DS1302_PORT &= ~_BV(DS1302_CE);
}

static uint8_t B2D(uint8_t bcd)
{
	return (bcd >> 4) * 10 + (bcd & 0x0F);
}

static uint8_t D2B(uint8_t decimal)
{
	return (((decimal / 10) << 4) | (decimal % 10));
}

void DS1302_GetTime(_rtc *rtc)
{
	uint8_t buffer[8] = {0,};
	
	DS1302_RxBurst(buffer);
	rtc->sec = B2D(buffer[0] & 0x7F);
	rtc->min = B2D(buffer[1] & 0x7F);	
	rtc->hour = B2D(buffer[2] & 0x1F);
	rtc->day = B2D(buffer[3] & 0x3F);
	rtc->month = B2D(buffer[4] & 0x1F);
	rtc->wday = buffer[5] & 0x07;
	rtc->year = B2D(buffer[6]);
}

void DS1302_SetTime(_rtc *rtc)
{	
	/* Clear WP */
	DS1302_TxReg(DS1302_REG_WP, 0x00);
		
	DS1302_TxReg(DS1302_REG_SEC, D2B(rtc->sec));		
	DS1302_TxReg(DS1302_REG_MIN, D2B(rtc->min));
	DS1302_TxReg(DS1302_REG_HOUR, D2B(rtc->hour));
	DS1302_TxReg(DS1302_REG_DATE, D2B(rtc->day));
	DS1302_TxReg(DS1302_REG_MONTH, D2B(rtc->month));
	DS1302_TxReg(DS1302_REG_DAY, rtc->wday);
	DS1302_TxReg(DS1302_REG_YEAR, D2B(rtc->year));
}