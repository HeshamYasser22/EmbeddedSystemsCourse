/*
 * ICU_Program.c
 *
 *  Created on: ٠٩‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */
#include "ICU_Interface.h"
#include <avr/io.h>


void ICU_Init(void)
{
	CLR_BIT(DDRD, PD6);
	Timer1_SetWaveMode(0b0000);
	Timer1_SetInterruptState(0b0000);
	Timer1_SetClkSource(BY256);
}

void ICU_SetFallingEdge(void)
{
	Timer1_SetCaptureEdge(FALLING);
}
void ICU_SetRisingEdge(void)
{
	Timer1_SetCaptureEdge(RISING);
}

int ICU_ReadICR(void)
{
	return Timer1_ReadICR();
}



