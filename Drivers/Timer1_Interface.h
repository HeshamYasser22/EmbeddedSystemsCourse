/*
 * Timer1_Interface.h
 *
 *  Created on: ٠٧‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "avr/io.h"
#include "BIT_LIB.h"


enum CompareOutMode {NORMAL, TOGGLE, CLEAR, SET};
typedef enum CompareOutMode CompareOutMode_e;

void Timer1_SetOutCompareMode_A (CompareOutMode_e Mode);
void Timer1_SetOutCompareMode_B (CompareOutMode_e Mode);

void Timer1_SetWaveMode (char Mode);
enum ClkSrc {NO, BY1, BY8, BY64, BY256, BY1024, EX_FALLING, EX_RISING};
typedef enum ClkSrc ClkSrc_e;
void Timer1_SetClkSource (ClkSrc_e Src);

void Timer1_SetTCNT(int TCNT_Value);
void Timer1_SetOCR1A(int OCR1A_Value);
void Timer1_SetOCR1B(int OCR1B_Value);
void Timer1_SetICR1 (int ICR1_Value);
typedef enum {FALLING, RISING} ICU_EDGE_e;
void Timer1_SetCaptureEdge(ICU_EDGE_e Edge);
int Timer1_ReadICR(void);
/*
 * Set the Wanted Bits from the following:-
 * 		TICIE1 | OCIE1A | OCIE1B | TOIE1
 */
void Timer1_SetInterruptState(char State);
char Timer1_ReadCaptureMode(void);

char Timer1_GetICUFlag(void);

void Timer1_ClearICUFlag(void);

#endif /* TIMER1_INTERFACE_H_ */
