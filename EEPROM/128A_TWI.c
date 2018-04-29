/*
 * _128A_TWI.c
 *
 * Created: 2018-04-11 오전 8:09:01
 *  Author: kiki
 */ 

#include "128A_TWI.h"

static bool TWI_Start(void);
static bool TWI_Restart(void);
static bool TWI_Stop(void);
static bool TWI_TxDeviceAddr(uint8_t deviceAddr);
static bool TWI_TxData(uint8_t data);
static bool TWI_RxAck(uint8_t *data);
static bool TWI_RxNack(uint8_t *data);

void TWI_Init(void)
{
	/* Pin Configuration */
	TWI_DDR |= _BV(SCL_OUT)|_BV(SDA_OUT);
	
	/* 8MHz / (16 + 2 * TWBR * 4^TWPS) = 200kHz */
	TWBR = 16;
	TWSR = 0;
}

bool TWI_RxBuffer(uint8_t deviceAddr, uint8_t registerAddr, uint8_t *data, uint8_t length)
{
	/* Start 비트 전송 */
	if(!TWI_Start()) return false;
	
	/* 쓰기 모드로 Device 주소 전송 */
	if(!TWI_TxDeviceAddr((deviceAddr << 1) | TWI_WRITE)) return false;
	
	/* 레지스터 전송 */
	if(!TWI_TxData(registerAddr)) return false;
	
	/* 읽기로 전환을 위해서 재시작 */
	if(!TWI_Restart()) return false;
	
	/* 읽기 모드로 Device 주소 전송 */
	if(!TWI_TxDeviceAddr((deviceAddr << 1) | TWI_READ)) return false;
	
	/* 데이터 수신 시 Ack 전송, 마지막 데이터는 Nack 전송  */
	for(uint8_t i = 0; i < length; i++)
	{
		if(i < length -1)
		{
			if(!TWI_RxAck(data + i)) return false;
		}
		else
		{
			if(!TWI_RxNack(data + i)) return false;
		}
	}
	
	/* Stop 비트 전송 */
	if(!TWI_Stop()) return false;
	
	return true;
}

bool TWI_TxBuffer(uint8_t deviceAddr, uint8_t registerAddr, uint8_t *data, uint8_t length)
{
	/* Start 비트 전송 */
	if(!TWI_Start()) return false;
	
	/* 쓰기 모드로 Device 주소 전송 */
	if(!TWI_TxDeviceAddr((deviceAddr << 1) | TWI_WRITE)) return false;
	
	/* 레지스터 전송 */
	if(!TWI_TxData(registerAddr)) return false;
	
	/* 데이터 송신 */
	for(uint8_t i = 0; i < length; i++)
	{
		if(!TWI_TxData(*(data+i))) return false;
	}
	
	/* Stop 비트 전송 */
	if(!TWI_Stop()) return false;
	
	return true;
}

static bool TWI_Start()
{
	/* Send START condition */
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);	
	
	/* Wait for TWINT flag */
	while((TWCR & _BV(TWINT)) == 0);
	
	/* Check value of TWI Status Register */
	if((TWSR & TWI_TWS_MASK) != TWI_START) return false;
	
	return true;
}

static bool TWI_Restart()
{
	/* Send START condition */
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	
	/* Wait for TWINT flag */
	while((TWCR & _BV(TWINT)) == 0);
	
	/* Check value of TWI Status Register */
	if((TWSR & TWI_TWS_MASK) != TWI_RESTART) return false;
	
	return true;
}

static bool TWI_Stop()
{
	/* Send STOP condition */
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	
	return true;
}

static bool TWI_TxDeviceAddr(uint8_t deviceAddr)
{
	/* Load Data into TWDR Register */
	TWDR = deviceAddr;
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	/* Wait for TWINT Flag set */
	while((TWCR & _BV(TWINT)) == 0);
	
	if(deviceAddr & 0x01)
	{
		/* READ Mode, Check value of TWI Status Register */
		if((TWSR & TWI_TWS_MASK) != TWI_MR_SLA_ACK) return false;
	}
	else
	{
		/* WRITE Mode, Check value of TWI Status Register */
		if((TWSR & TWI_TWS_MASK) != TWI_MT_SLA_ACK) return false;
	}
	
	return true;
}

static bool TWI_TxData(uint8_t data)
{
	/* Load Data into TWDR Register */
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	/* Wait for TWINT Flag set */
	while((TWCR & _BV(TWINT)) == 0);
	
	/* Check value of TWI Status Register */
	if((TWSR & TWI_TWS_MASK) != TWI_MT_DATA_ACK) return false;
	
	return true;
}

static bool TWI_RxAck(uint8_t *data)
{
	/* 마스터 수신 모드에서 데이터 수신 시 마다 ACK 전송 */
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	
	/* Wait for TWINT Flag set */
	while((TWCR & _BV(TWINT)) == 0);
	
	/* Check value of TWI Status Register */
	if((TWSR & TWI_TWS_MASK) != TWI_MR_DATA_ACK) return false;
	
	/* 데이터 수신 */
	*data = TWDR;
	return true;
}

static bool TWI_RxNack(uint8_t *data)
{
	/* 마스터 수신 모드에서 최종 데이터 수신 시 NACK 전송 (ACK를 전송하지 않으면 됨) */
	TWCR = _BV(TWINT) | _BV(TWEN);
	
	/* Wait for TWINT Flag set */
	while((TWCR & _BV(TWINT)) == 0);
	
	/* Check value of TWI Status Register */
	if((TWSR & TWI_TWS_MASK) != TWI_MR_DATA_NACK) return false;
	
	/* 데이터 수신 */
	*data = TWDR;
	return true;
}