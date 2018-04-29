/*
 * EEPROM.c
 *
 * Created: 2018-04-26 오후 11:07:14
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "AT24C02.h"
#include "128A_USART.h"

static int8_t TestEEPROM();
static int8_t retVal;

int main(void)
{
	USART0_Init();
	retVal = TestEEPROM();		
	if(retVal != 0)
	{
		char msg[50];
		sprintf(msg, "TestEEPROM failed:[%d]\r\n", retVal);		
		USART0_TxBuffer((uint8_t*)msg, strlen(msg));
	}
			
    /* Replace with your application code */
    while (1) 
    {
    }
}

static int8_t TestEEPROM()
{
	uint8_t data = 0;
	uint8_t sndBuf[30] = {'x','x','x','l','o',' ','W','o','r','l','d','!',' ','H','a','v','e',' ','f','u','n','!','\r','\n',};
	uint8_t rcvBuf[30] = {0, };
	
	if(!EEPROM_EraseAll()) return 1;
	if(!EEPROM_ReadByte(0x00, &data)) return 2;
	if(data != 0x00) return 3;
	
	if(!EEPROM_ReadByte(0xF0, &data)) return 4;
	if(data != 0x00) return 5;
	
	if(!EEPROM_ReadByte(0xFF, &data)) return 6;
	if(data != 0x00) return 7;

	if(!EEPROM_WriteByte(0x00, 'H')) return 8;
	if(!EEPROM_ReadByte(0x00, &data)) return 9;
	sndBuf[0] = data;
	
	if(!EEPROM_WriteByte(0x01, 'e')) return 10;
	if(!EEPROM_ReadByte(0x01, &data)) return 11;
	sndBuf[1] = data;
	
	if(!EEPROM_WriteByte(0x02, 'l')) return 12;
	if(!EEPROM_ReadByte(0x02, &data)) return 13;
	sndBuf[2] = data;
	
	if(!EEPROM_WriteBuffer(0, sndBuf, strlen((char*)sndBuf))) return 14;
	if(!EEPROM_ReadBuffer(0, rcvBuf, strlen((char*)sndBuf))) return 15;
	
	for(int i = 0; i < strlen((char*)sndBuf);i++)
	{
		if(sndBuf[i] != rcvBuf[i]) return 16;
	}
	
	memset(rcvBuf, 0, sizeof(rcvBuf));
	
	if(!EEPROM_WriteBuffer(5, sndBuf, strlen((char*)sndBuf))) return 17;
	if(!EEPROM_ReadBuffer(5, rcvBuf, strlen((char*)sndBuf))) return 18;
	
	for(int i = 0; i < strlen((char*)sndBuf);i++)
	{
		if(sndBuf[i] != rcvBuf[i]) return 19;
	}	
	
	USART0_TxBuffer((uint8_t*)rcvBuf, strlen((char*)rcvBuf));
		
	return 0;
}
