/*
 * IrReceiver.c
 *
 * Created: 2018-04-19 오후 8:53:51
 *  Author: kiki
 */ 

#include <avr/interrupt.h>
#include "IrReceiver.h"
#include "../USART/128A_USART.h"

static volatile uint32_t IR_RcvData;
static volatile uint8_t RcvBits;
cbFuncPtr pfCallback;

static void IR_Decode();

ISR(INT5_vect)
{		
	IR_Decode();
}

void IR_Init(cbFuncPtr funcPtr)
{
	pfCallback = funcPtr;
			
	/* Configure Interrupt, falling edge */
	EIMSK |= _BV(IR_EXTI);
	
	/* 인터럽트에 따라서 레지스터가 EICRA 또는 EICRB로 바뀌니 주의 */
	EICRB |= _BV(ISC51);
	
	/* 시간 측정용 T0 타이머 Enable, 8MHz / 1024 = 7812.5Hz = 128us */
	TCCR0 |= _BV(CS02) | _BV(CS01) | _BV(CS00);
	
	RcvBits = 32;
	sei();
}


static void IR_Decode()
{
	uint8_t time = TCNT0;
	uint8_t overflow = TIFR & _BV(TOV0);
	
	/* 리드 펄스를 수신하지 않은 상황 */
	if(RcvBits == 32)
	{
		/* 첫번 째 데이터가 들어올 때까지의 시간을 확인해서 Normal 데이터인지 Repeat 데이터인지 확인 */
		if(time > IR_NORMAL_LEAD_CLK_MIN && time < IR_NORMAL_LEAD_CLK_MAX && !overflow)
		{
			//Normal Lead
			IR_RcvData = 0;
			RcvBits = 0;
		}
		else if(time > IR_REPEAT_LEAD_CLK_MIN && IR_REPEAT_LEAD_CLK_MAX && !overflow)
		{
			//Repeat Lead
			pfCallback(IR_RcvData);
		}
	}
	else
	{
		/* 비정상적으로 긴 시그널은 무효처리 */
		if(time > IR_BIT_CLK_MAX || overflow)
		{
			RcvBits = 32;
		}
		else
		{
			if(time > IR_BIT_CLK_DIFF)
			{
				/* 1 수신 */
				IR_RcvData = (IR_RcvData << 1) + 1;
			}
			else
			{
				/* 0 수신 */
				IR_RcvData = IR_RcvData << 1;
			}
			
			/* RcvBits 0~31, 총 32비트 수신 시 완료 */
			if(RcvBits == 31)
			{
				pfCallback(IR_RcvData);
			}
			
			RcvBits++;
		}
	}
	
	TCNT0 = 0;
	TIFR |= _BV(TOV0);
}