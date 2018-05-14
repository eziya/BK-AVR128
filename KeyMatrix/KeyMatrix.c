/*
 * KeyMatrix.c
 *
 * Created: 2018-05-14 오후 2:26:27
 *  Author: kiki
 */ 

#include "KeyMatrix.h"

uint8_t KM_State[16];

void KM_ReadState()
{
	/* COL1(Output LOW) 상태에서 ROW1~3(Input Pull-up) 상태 확인 (COL2,3,4 Hi-Z 상태) */
	KM_DDR = 0;
	KM_PORT = 0;
	KM_PIN = 0;
	
	KM_DDR |= _BV(KM_COL1);
	KM_PORT &= ~_BV(KM_COL1);
	KM_PORT |= _BV(KM_ROW1) | _BV(KM_ROW2) | _BV(KM_ROW3);
	
	if(KM_PIN & _BV(KM_ROW1)) KM_State[0] = 0;
	else KM_State[0] = 1;
	
	if(KM_PIN & _BV(KM_ROW2)) KM_State[4] = 0;
	else KM_State[4] = 1;
	
	if(KM_PIN & _BV(KM_ROW3)) KM_State[8] = 0;
	else KM_State[8] = 1;
	
	if(KM_PIN & _BV(KM_ROW4)) KM_State[12] = 0;
	else KM_State[12] = 1;
	
	/* COL2(Output LOW) 상태에서 ROW1~3(Input Pull-up) 상태 확인 (COL1,3,4 Hi-Z 상태) */
	KM_DDR = 0;
	KM_PORT = 0;
	KM_PIN = 0;
	
	KM_DDR |= _BV(KM_COL2);
	KM_PORT &= ~_BV(KM_COL2);
	KM_PORT |= _BV(KM_ROW1) | _BV(KM_ROW2) | _BV(KM_ROW3);
	
	if(KM_PIN & _BV(KM_ROW1)) KM_State[1] = 0;
	else KM_State[1] = 1;
	
	if(KM_PIN & _BV(KM_ROW2)) KM_State[5] = 0;
	else KM_State[5] = 1;
	
	if(KM_PIN & _BV(KM_ROW3)) KM_State[9] = 0;
	else KM_State[9] = 1;
	
	if(KM_PIN & _BV(KM_ROW4)) KM_State[13] = 0;
	else KM_State[13] = 1;	
	
	/* COL3(Output LOW) 상태에서 ROW1~3(Input Pull-up) 상태 확인 (COL1,2,4 Hi-Z 상태) */
	KM_DDR = 0;
	KM_PORT = 0;
	KM_PIN = 0;
	
	KM_DDR |= _BV(KM_COL3);
	KM_PORT &= ~_BV(KM_COL3);
	KM_PORT |= _BV(KM_ROW1) | _BV(KM_ROW2) | _BV(KM_ROW3);
	
	if(KM_PIN & _BV(KM_ROW1)) KM_State[2] = 0;
	else KM_State[2] = 1;
	
	if(KM_PIN & _BV(KM_ROW2)) KM_State[6] = 0;
	else KM_State[6] = 1;
	
	if(KM_PIN & _BV(KM_ROW3)) KM_State[10] = 0;
	else KM_State[10] = 1;
	
	if(KM_PIN & _BV(KM_ROW4)) KM_State[14] = 0;
	else KM_State[14] = 1;
	
	/* COL4(Output LOW) 상태에서 ROW1~3(Input Pull-up) 상태 확인 (COL1,2,3 Hi-Z 상태) */
	KM_DDR = 0;
	KM_PORT = 0;
	KM_PIN = 0;
	
	KM_DDR |= _BV(KM_COL4);
	KM_PORT &= ~_BV(KM_COL4);
	KM_PORT |= _BV(KM_ROW1) | _BV(KM_ROW2) | _BV(KM_ROW3);
	
	if(KM_PIN & _BV(KM_ROW1)) KM_State[3] = 0;
	else KM_State[3] = 1;
	
	if(KM_PIN & _BV(KM_ROW2)) KM_State[7] = 0;
	else KM_State[7] = 1;
	
	if(KM_PIN & _BV(KM_ROW3)) KM_State[11] = 0;
	else KM_State[11] = 1;
	
	if(KM_PIN & _BV(KM_ROW4)) KM_State[15] = 0;
	else KM_State[15] = 1;
}

