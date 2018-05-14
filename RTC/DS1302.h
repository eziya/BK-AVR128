/*
 * DS1302.h
 *
 * Created: 2018-05-14 오전 8:09:47
 *  Author: kiki
 */ 


#ifndef DS1302_H_
#define DS1302_H_

#include <avr/io.h>

#define DS1302_DDR		DDRE	
#define DS1302_PORT		PORTE
#define DS1302_PIN		PINE

#define DS1302_SCLK		PE2		
#define DS1302_IO		PE3
#define DS1302_CE		PE4		

#define DS1302_REG_SEC		0
#define DS1302_REG_MIN		1
#define DS1302_REG_HOUR		2
#define DS1302_REG_DATE		3
#define DS1302_REG_MONTH	4
#define DS1302_REG_DAY		5
#define DS1302_REG_YEAR		6
#define DS1302_REG_WP		7

typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t wday;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
} _rtc;

extern char *wday[8];

void DS1302_Init(void);
void DS1302_GetTime(_rtc *rtc);
void DS1302_SetTime(_rtc *rtc);

#endif /* DS1302_H_ */