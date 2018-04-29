/*
 * _128A_TWI.h
 *
 * Created: 2018-04-11 오전 8:08:44
 *  Author: kiki
 */ 

#ifndef __128A_TWI_H_
#define __128A_TWI_H_

#include <avr/io.h>
#include <stdbool.h>

#define TWI_DDR		DDRD
#define TWI_PORT	PORTD
#define SCL_OUT		PD0
#define SDA_OUT		PD1

/* Read Write Flag */
#define TWI_WRITE	0x00
#define TWI_READ	0x01

/* Status Register Mask */
#define TWI_TWS_MASK	0xF8

/* TWI Status Code */
#define TWI_START		0x08
#define TWI_RESTART		0x10
#define TWI_LOST		0x38

/* TWI Status Code for Master Transmit */
#define TWI_MT_SLA_ACK		0x18
#define TWI_MT_SLA_NACK		0x20
#define TWI_MT_DATA_ACK		0x28
#define TWI_MT_DATA_NACK	0x30

/* TWI Status Code for Master Receive */
#define TWI_MR_SLA_ACK		0x40
#define TWI_MR_SLA_NACK		0x48
#define TWI_MR_DATA_ACK		0x50
#define TWI_MR_DATA_NACK	0x58

void TWI_Init(void);
bool TWI_RxBuffer(uint8_t deviceAddr, uint8_t registerAddr, uint8_t *data, uint8_t length);
bool TWI_TxBuffer(uint8_t deviceAddr, uint8_t registerAddr, uint8_t *data, uint8_t length);

#endif /* __128A_TWI_H_ */