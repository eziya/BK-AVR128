/*
 * DS18B20.h
 *
 * Created: 2018-04-21 오후 12:00:53
 *  Author: kiki
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>
#include <stdbool.h>

#define DS18B20_RESOLUTION		12
#define DS18B20_CONV_TIME		750
#define DS18B20_TEMP_STEP		0.0625

#define CMD_ROM_SEARCH			0xF0
#define CMD_ROM_READ			0x33
#define CMD_ROM_MATCH			0x55
#define CMD_ROM_SKIP			0xCC
#define CMD_ROM_ALARM			0xEC

#define CMD_FUNC_CONVERT		0x44
#define CMD_FUNC_WRITE_SCRATCH	0x4E
#define CMD_FUNC_READ_SCRATCH	0xBE
#define CMD_FUNC_COPY_SCRATCH	0x48
#define CMD_FUNC_RECALL			0xB8
#define CMD_FUNC_READ_SUPPLY	0xB4

bool DS18B20_ReadROMCode(uint8_t *buffer, uint8_t length);
bool DS1B20_ReadTemp(float *degree);

#endif /* DS18B20_H_ */