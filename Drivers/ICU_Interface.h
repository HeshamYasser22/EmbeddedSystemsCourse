/*
 * ICU_Interface.h
 *
 *  Created on: ٠٩‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */

#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

#include "Timer1_Interface.h"
#include <avr/interrupt.h>

void ICU_Init(void);

void ICU_SetFallingEdge(void);
void ICU_SetRisingEdge(void);


int ICU_ReadICR(void);
int ICU_CalculateFrequency(void);
int ICU_CalculateDuty(void);

int ICU_TOTAL(void);
int ICU_ON(void);
#endif /* ICU_INTERFACE_H_ */
