/*
 * IrReceiver.h
 *
 * Created: 2018-04-19 오후 8:53:39
 *  Author: kiki
 */ 


#ifndef IRRECEIVER_H_
#define IRRECEIVER_H_

#include <avr/io.h>

#define IR_DDR		DDRE
#define IR_PORT		PORTE
#define IR_PIN		PINE
#define IR_DATA		PE5
#define IR_EXTI		INT5

/*
* Normal Data Lead Length : 13.5ms (105.46 clock)
* Repeat Data Lead Length : 11.25ms (87.89 clock)
* Bit 0 Length : 1.125ms (8.78 clock)
* Bit 1 Length : 2.25ms (17.57 clock)
*/

#define IR_NORMAL_LEAD_CLK_MIN		100
#define IR_NORMAL_LEAD_CLK_MAX		110
#define IR_REPEAT_LEAD_CLK_MIN		82
#define IR_REPEAT_LEAD_CLK_MAX		92
#define IR_BIT_CLK_DIFF				13
#define IR_BIT_CLK_MAX				21

typedef void (*cbFuncPtr)(uint32_t);
void IR_Init(cbFuncPtr funcPtr);

#endif /* IRRECEIVER_H_ */