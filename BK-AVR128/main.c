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

#include "Buzzer/Buzzer.h"
#include "Buzzer/Note.h"
#include "EEPROM/AT24C02.h"

static void PlayMusic();
static bool TestEEPROM();

int main(void)
{
	//PlayMusic();
	if(!TestEEPROM())
	{
		PlayMusic();
	}
	
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
	char sndBuf[30] = {'x','x','x','l','o',' ','w','o','r','l','d','!',};
	char rcvBuf[30] = {0, };

	if(!EEPROM_WriteByte(0x00, 'h')) return false;	
	if(!EEPROM_ReadByte(0x00, &data)) return false;	
	sndBuf[0] = data;
	
	if(!EEPROM_WriteByte(0x01, 'e')) return false;
	if(!EEPROM_ReadByte(0x01, &data)) return false;
	sndBuf[1] = data;
	
	if(!EEPROM_WriteByte(0x02, 'l')) return false;
	if(!EEPROM_ReadByte(0x02, &data)) return false;
	sndBuf[2] = data;
	
	if(!EEPROM_WriteBuffer(5, (uint8_t*)sndBuf, strlen(sndBuf))) return false;	
	if(!EEPROM_ReadBuffer(5, (uint8_t*)rcvBuf, strlen(sndBuf))) return false;
		
	for(int i = 0; i < strlen(sndBuf);i++)
	{
		if(sndBuf[i] != rcvBuf[i]) return false;		
	}
	
	return true;
}
