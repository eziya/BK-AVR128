/*
 * AT24C02.c
 *
 * Created: 2018-04-11 오전 8:09:44
 *  Author: kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000
#endif

#include "AT24C02.h"

bool EEPROM_ReadByte(uint8_t address, uint8_t *data)
{		
	return TWI_RxBuffer(AT24C02_ADDRESS, address, data, 1);	
}

bool EEPROM_ReadBuffer(uint8_t address, uint8_t *buffer, uint8_t length)
{
	for(uint8_t i=0; i < length; i++)
	{
		if(!EEPROM_ReadByte(address+i, buffer+i)) return false;
	}
	
	return true;
}

bool EEPROM_WriteByte(uint8_t address, uint8_t data)
{
	bool ret = TWI_TxBuffer(AT24C02_ADDRESS, address, &data, 1);	
	
	if(ret)	
	{
		_delay_ms(5);		
	}
	
	return ret;
}

bool EEPROM_WriteBuffer(uint8_t address, uint8_t *buffer, uint8_t length)
{
	/* Split writing for each pages 8, 16, 24, ...  */
	
	uint8_t startAddress = address;
		
	for(uint8_t i = 0; i < length; i++)
	{
		if( (address + i) % EEPROM_PAGE_SIZE == 0 && i != 0)
		{						
			uint8_t buflen = (address + i) - startAddress;
			if(!TWI_TxBuffer(AT24C02_ADDRESS, startAddress, buffer, buflen)) return false;
			startAddress += buflen;
			buffer += buflen;
							
			_delay_ms(5);
		}
	}
	
	/* Write last page */
	if(!TWI_TxBuffer(AT24C02_ADDRESS, startAddress, buffer, address + length - startAddress)) return false;
	_delay_ms(5);
	
	return true;
}

bool EEPROM_EraseAll(void)
{
	uint8_t zero[8] = {0,};
	uint16_t address = 0;
			
	while(address < EEPROM_TOTAL_SIZE)
	{				
		if(!TWI_TxBuffer(AT24C02_ADDRESS, address, zero, sizeof(zero))) return false;
		_delay_ms(5);
		address += EEPROM_PAGE_SIZE;
	}
	
	return true;
}