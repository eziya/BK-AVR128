/*
 * Buzzer.c
 *
 * Created: 2018-04-26 오후 11:04:32
 * Author : kiki
 */ 
#ifndef F_CPU
#define F_CPU	8000000L
#endif

#include <avr/io.h>
#include "Buzzer.h"
#include "Note.h"

static void PlayMusic();

int main(void)
{
	
	PlayMusic();
	
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

