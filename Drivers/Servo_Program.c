/*
 * Servo_Program.c
 *
 *  Created on: ٠٨‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */

#include "Servo_Interface.h"
void Servo_Init(void)
{
	SET_BIT(DDRD, PD5);
	Timer1_SetWaveMode(0b1110);
	Timer1_SetOutCompareMode_A(CLEAR);
	Timer1_SetICR1(20000);
	Timer1_SetInterruptState(0b0000);
	Timer1_SetClkSource(BY8);
}

void Servo_SendAngle(char Angle)
{
	int OCR1A_Value;
	if ((Angle >= 0) && (Angle <= 180))
	{
		OCR1A_Value = (int)(1000 + ((1000/180.0)*Angle));
		Timer1_SetOCR1A(OCR1A_Value);
	}
}

