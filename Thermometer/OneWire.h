/*
 * OneWire.h
 *
 * Created: 2018-04-21 오전 11:24:56
 *  Author: kiki
 */ 

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <util/delay.h>

#define OWI_DDR		DDRE
#define OWI_PORT	PORTE
#define OWI_PIN		PINE
#define OWI_DQ		PE6

#define OWI_SetDQTx()	OWI_DDR |= _BV(OWI_DQ);
#define OWI_SetDQRx()	OWI_DDR &= ~_BV(OWI_DQ);
#define OWI_SetDQHigh() OWI_PORT |= _BV(OWI_DQ);
#define OWI_SetDQLow()	OWI_PORT &= ~_BV(OWI_DQ);

uint8_t OWI_Init(void);
void OWI_TxBit(uint8_t bit);
uint8_t OWI_RxBit(void);
void OWI_TxByte(uint8_t data);
uint8_t OWI_RxByte(void);

#endif /* ONEWIRE_H_ */