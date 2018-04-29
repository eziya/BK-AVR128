/*
 * IrReceiver.c
 *
 * Created: 2018-04-26 오후 11:25:15
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "IrReceiver.h"
#include "128A_USART.h"

static void TestIrRecv();
void IrRcvCallback(uint32_t code);

int main(void)
{	
	USART0_Init();
	TestIrRecv();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

static void TestIrRecv()
{
	IR_Init(IrRcvCallback);
}

void IrRcvCallback(uint32_t code)
{
	char msg[30] = {0,};
	uint16_t address;
	uint8_t command;
	
	address = (code >> 16) & 0xFFFF;
	command = (code >> 8) & 0xFF;
	
	sprintf(msg, "ADDR:0x%04x,CMD:0x%04x\r\n", address, command);
	
	USART0_TxBuffer((uint8_t*)msg, strlen(msg));
}