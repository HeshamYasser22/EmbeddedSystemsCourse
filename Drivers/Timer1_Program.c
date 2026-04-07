/*
 * Timer1_Program.c
 *
 *  Created on: ٠٧‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */


#include "Timer1_Interface.h"


void Timer1_SetOutCompareMode_A (CompareOutMode_e Mode)
{
	if ((Mode >= 0) && (Mode <= 3))
	{
		TCCR1A &= ~(0b11 << COM1A0);
		TCCR1A |= (Mode << COM1A0);
	}

}
void Timer1_SetOutCompareMode_B (CompareOutMode_e Mode)
{
	if ((Mode >= 0) && (Mode <= 3))
	{
		TCCR1A &= ~(0b11 << COM1B0);
		TCCR1A |= (Mode << COM1B0);
	}
}

void Timer1_SetWaveMode (char Mode)
{
	if ((Mode >= 0) && (Mode <= 15))
	{
		TCCR1A &= ~(0b11 << WGM10);
		TCCR1A |= ((Mode&0b11) << WGM10);
		TCCR1B &= ~(0b11 << WGM12);
		TCCR1B |= ((Mode>>2) << WGM12);
	}
}
void Timer1_SetClkSource (ClkSrc_e Src)
{
	if ((Src >= 0) && (Src <= 7))
	{
		TCCR1B &= ~(0b111 << CS10);
		TCCR1B |= (Src << CS10);
	}
}

void Timer1_SetTCNT(int TCNT_Value)
{
	TCNT1 = TCNT_Value;
}
void Timer1_SetOCR1A(int OCR1A_Value)
{
	OCR1A = OCR1A_Value;
}
void Timer1_SetOCR1B(int OCR1B_Value)
{
	OCR1B = OCR1B_Value;
}
void Timer1_SetICR1 (int ICR1_Value)
{
	ICR1 = ICR1_Value;
}

void Timer1_SetInterruptState(char State)
{
	if ((State >= 0) && (State <= 15))
	{
		TIMSK &= ~(0b1111 << TOIE1);
		TIMSK |= (State << TOIE1);
	}
}

