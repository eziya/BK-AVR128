/*
 * DS18B20.c
 *
 * Created: 2018-04-21 오후 12:00:41
 *  Author: kiki
 */ 

#include "DS18B20.h"
#include "OneWire.h"

bool DS18B20_ReadROMCode(uint8_t *buffer, uint8_t length)
{	
	/* No Presence pulse ERROR */
	if(OWI_Init()) return false;
	
	/* ROM Command */	
	OWI_TxByte(CMD_ROM_READ);
	
	/* Function Command */
	for(int i=0; i < length; i++)
	{
		buffer[i] = OWI_RxByte();
	}	
	
	return true;
}

bool DS1B20_ReadTemp(float *degree)
{
	uint8_t buffer[9];
	
	/* No Presence pulse ERROR */
	if(OWI_Init()) return false;
	
	/* ROM Command */
	OWI_TxByte(CMD_ROM_SKIP);
	
	/* Function Command */
	OWI_TxByte(CMD_FUNC_CONVERT);
	
	/* Wait 1 from DS1B20 */
	while(!OWI_RxBit());
	
	/* No Presence pulse ERROR */
	if(OWI_Init()) return false;
	
	/* ROM Command */
	OWI_TxByte(CMD_ROM_SKIP);
	
	/* Function Command */
	OWI_TxByte(CMD_FUNC_READ_SCRATCH);
	
	/* Reading scratchpad */
	for(int i=0; i < 9; i++)
	{
		buffer[i] = OWI_RxByte();
	}
	
	uint16_t temp = (buffer[1] << 8) | buffer[0];
	if(temp & 0x8000)
	{
		/* Negative Value, 2의 보수 + 1 */
		temp = ~temp;
		temp += 1;
		
		*degree = DS18B20_TEMP_STEP * temp * -1;
	}
	else
	{
		*degree = DS18B20_TEMP_STEP * temp;
	}
	
	return true;
}