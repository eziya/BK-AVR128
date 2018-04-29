/*
* OneWire.c
*
* Created: 2018-04-21 오전 11:25:05
*  Author: kiki
*/

#include "OneWire.h"

static uint8_t dqBit = 0;

uint8_t OWI_Init()
{
	dqBit = 0;
	
	/* Reset Pulse, 500us */
	OWI_SetDQLow();
	OWI_SetDQTx();
	_delay_us(500);
	
	/* Release line, Wait 80us */
	OWI_SetDQRx();
	_delay_us(80);
	
	/* Read DQ Pin*/
	dqBit = (OWI_PIN & _BV(OWI_DQ));
	_delay_us(420);
	
	/* dqBit = [0:OK, 1:ERROR] */
	return dqBit;
}

void OWI_TxBit(uint8_t bit)
{
	/* Tx time slot 80us */
	if(bit)
	{
		/* Pull-down 2us */
		OWI_SetDQLow();
		OWI_SetDQTx();
		_delay_us(2);
		
		/* Pull-up */
		OWI_SetDQRx();
		
		/* Wait Tx time slot */
		_delay_us(78);
	}
	else
	{
		/* Pull down 2us */
		OWI_SetDQLow();
		OWI_SetDQTx();
		
		/* Wait Tx time slot */
		_delay_us(78);
		OWI_SetDQRx();
		
		/* Recovery time */
		_delay_us(2);
	}
}

uint8_t OWI_RxBit()
{
	/* Rx time slot 80us */
	dqBit = 0;
	
	/* Pull down 2us */
	OWI_SetDQLow();
	OWI_SetDQTx();
	_delay_us(2);
	
	/* Release line */
	OWI_SetDQRx();
	
	/* Read DQ pin */
	_delay_us(10);
	if(OWI_PIN & _BV(OWI_DQ))	dqBit = 1;
	
	/* Read Slot 시간 대기 */
	_delay_us(68);
	
	return dqBit;
}

void OWI_TxByte(uint8_t data)
{
	for(int i = 0; i < 8; i++)
	{
		OWI_TxBit(data & 0x01);
		data >>= 1;
	}
}

uint8_t OWI_RxByte()
{
	uint8_t ret = 0;
	
	for(int i=0; i < 8; i++)
	{
		ret |= (OWI_RxBit() << i);
	}
	
	return ret;
}
