/*
 * BK-AVR128.c
 *
 * Created: 2018-04-10 오후 9:23:38
 * Author : kiki
 */ 

#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#include "USART/128A_USART.h"
#include "Buzzer/Buzzer.h"
#include "Buzzer/Note.h"
#include "EEPROM/AT24C02.h"
#include "LED/PWM_LED.h"
#include "FND/74HC573.h"

static void PlayMusic();
static bool TestEEPROM();
static void TestPWMLED();
static void TestFND();

int main(void)
{
	USART0_Init();
	
	/*
	PlayMusic();
	
	if(!TestEEPROM())
	{
		char *msg = "TestEEPROM failed\r\n";
		USART0_TxBuffer((uint8_t*)msg, strlen(msg));
	}	
	
	TestPWMLED();
	*/
	
	TestFND();
	
	/* Replace with your application code */
    while (1) 
    {
		
    }
}

static void PlayMusic()
{
	/* C:도, D:레, E:미, F:파, G:솔, A:라, B:시 */
	uint16_t melody[] = { NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_G5 };
	uint8_t duration[] = { 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 4, 4 };
	
	for(int i = 0; i < sizeof(duration); i++)
	{
		uint16_t noteDuration = 1600 / duration[i];
		GPIO_MakeSound(melody[i], 50, noteDuration);		
	}
}

static bool TestEEPROM()
{
	uint8_t data = 0;
	uint8_t sndBuf[30] = {'x','x','x','l','o',' ','W','o','r','l','d','!',' ','H','a','v','e',' ','f','u','n','!','\r','\n',};
	uint8_t rcvBuf[30] = {0, };
		
	if(!EEPROM_EraseAll()) return false;
	if(!EEPROM_ReadByte(0x00, &data)) return false;	
	if(data != 0x00) return false;
	
	if(!EEPROM_ReadByte(0xF0, &data)) return false;
	if(data != 0x00) return false;
	
	if(!EEPROM_ReadByte(0xFF, &data)) return false;
	if(data != 0x00) return false;

	if(!EEPROM_WriteByte(0x00, 'H')) return false;	
	if(!EEPROM_ReadByte(0x00, &data)) return false;	
	sndBuf[0] = data;
	
	if(!EEPROM_WriteByte(0x01, 'e')) return false;
	if(!EEPROM_ReadByte(0x01, &data)) return false;
	sndBuf[1] = data;
	
	if(!EEPROM_WriteByte(0x02, 'l')) return false;
	if(!EEPROM_ReadByte(0x02, &data)) return false;
	sndBuf[2] = data;
	
	if(!EEPROM_WriteBuffer(0, sndBuf, strlen((char*)sndBuf))) return false;
	if(!EEPROM_ReadBuffer(0, rcvBuf, strlen((char*)sndBuf))) return false;
	
	for(int i = 0; i < strlen((char*)sndBuf);i++)
	{
		if(sndBuf[i] != rcvBuf[i]) return false;
	}
	
	memset(rcvBuf, 0, sizeof(rcvBuf));
	
	if(!EEPROM_WriteBuffer(5, sndBuf, strlen((char*)sndBuf))) return false;	
	if(!EEPROM_ReadBuffer(5, rcvBuf, strlen((char*)sndBuf))) return false;
		
	for(int i = 0; i < strlen((char*)sndBuf);i++)
	{
		if(sndBuf[i] != rcvBuf[i]) return false;		
	}
	
	USART0_TxBuffer(rcvBuf, strlen((char*)rcvBuf));			
	
	return true;
}

static void TestPWMLED()
{
	LED_Init();
	
	while(true)
	{
		for(int i=0; i < 256; i++)
		{
			LED_SetDuty(i);
			_delay_ms(10);
		}
	}	
}

static void TestFND()
{
	LATCH_Init();
	LATCH_On(_BV(LATCH_OUT1) | _BV(LATCH_OUT2));
	
	for(int i = 0; i < 10000; i++)
	{
		for(int j = 0; j < 5; j++)
		{	
			/* Display numbers */		
			int val = i;
			
			LATCH_SetDigit(DIGIT8);
			LATCH_SetSegment(FND_Numbers[val%10], false);
			_delay_ms(1);
			
			val = val / 10;
			
			LATCH_SetDigit(DIGIT7);
			LATCH_SetSegment(FND_Numbers[val%10], false);
			_delay_ms(1);
			
			val = val / 10;
			
			LATCH_SetDigit(DIGIT6);
			LATCH_SetSegment(FND_Numbers[val%10],  false);
			_delay_ms(1);
			
			val = val / 10;
			
			LATCH_SetDigit(DIGIT5);
			LATCH_SetSegment(FND_Numbers[val%10], false);
			_delay_ms(1);			
			
			/* Display characters */
			LATCH_SetDigit(DIGIT1);
			LATCH_SetSegment(FND_Chars[0], false);
			_delay_ms(1);
			
			LATCH_SetDigit(DIGIT2);
			LATCH_SetSegment(FND_Chars[1], false);
			_delay_ms(1);
			
			LATCH_SetDigit(DIGIT3);
			LATCH_SetSegment(FND_Chars[2], false);
			_delay_ms(1);
			
			LATCH_SetDigit(DIGIT4);
			LATCH_SetSegment(FND_Chars[3], false);
			_delay_ms(1);
		}
	}
	
	LATCH_Off(_BV(LATCH_OUT1) | _BV(LATCH_OUT2));	
}