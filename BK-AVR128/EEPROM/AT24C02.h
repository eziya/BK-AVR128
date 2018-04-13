/*
 * AT24C02.h
 *
 * Created: 2018-04-11 오전 8:09:25
 *  Author: kiki
 */ 


#ifndef AT24C02_H_
#define AT24C02_H_

#include "128A_TWI.h"
#include "../Common.h"

#define AT24C02_ADDRESS		0x50

#define EEPROM_PAGE_SIZE	8
#define EEPROM_TOTAL_SIZE	256

bool EEPROM_ReadByte(uint8_t address, uint8_t *data);
bool EEPROM_ReadBuffer(uint8_t address, uint8_t *buffer, uint8_t length);
bool EEPROM_WriteByte(uint8_t address, uint8_t data);
bool EEPROM_WriteBuffer(uint8_t address, uint8_t *buffer, uint8_t length);
bool EEPROM_EraseAll(void);

#endif /* AT24C02_H_ */