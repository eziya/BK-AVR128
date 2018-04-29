/*
 * _128A_USART.h
 *
 * Created: 2018-04-14 오전 8:38:56
 *  Author: kiki
 */ 


#ifndef __128A_USART_H_
#define __128A_USART_H_

#include <avr/io.h>
#include <stdbool.h>

#define USART0_TIMEOUT	1000	/* loop */
#define USART0_BAUDRATE	9600

void USART0_Init();
bool USART0_RxByte(uint8_t *data);
void USART0_TxByte(uint8_t data);
bool USART0_RxBuffer(uint8_t *buffer, uint16_t len);
void USART0_TxBuffer(uint8_t *buffer, uint16_t len);

#endif /* 128A_USART_H_ */