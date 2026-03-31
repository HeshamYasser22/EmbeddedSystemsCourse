/*
 * Program.c
 *
 *  Created on: 
 *      Author: Hesha
 */
#define F_CPU    8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LIB/STD_BIT.h"


#define NORMAL_MODE 0b00
#define PWM_MODE    0b01
#define CTC_MODE    0b10
#define FAST_PWM_MODE 0b11
void Timer0_SetMode(char Mode);

#define NORMAL_PORT 0b00
#define TGL_MODE	0b01
#define CLEAR_MODE  0b10
#define SET_MODE	0b11
void Timer0_SetCompareOutputMode (char Mode);

#define NOCLK       0b000
#define CLKBY1		0b001
#define CLKBY8		0b010
#define CLKBY64		0b011
#define CLKBY256	0b100
#define CLKBY1024	0b101
void Timer0_SetClkPrescaler (char Prescale);

void Timer0_SetTCNT (char TCNT_Value);
void Timer0_SetOCR (char OCR_Value);
void Timer0_EnableOverflowInterrupt();
void Timer0_DisableOverflowInterrupt();

void Timer0_EnableCompareInterrupt();
void Timer0_DisableCompareInterrupt();

void Timer0_InitPWM(void);
void Timer0_InitNormal(void);

char Timer0_CheckOverflow();

void main (void)
{
	SET_BIT(DDRA, PA0);
	CLR_BIT(PORTA, PA0);
	sei();
	Timer0_InitNormal();
	while (1)
	{
	}
}

void Timer0_SetMode(char Mode)
{
	switch (Mode)
	{
		case NORMAL_MODE:
			CLR_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
			break;
		case PWM_MODE:
			SET_BIT(TCCR0, WGM00);
			CLR_BIT(TCCR0, WGM01);
			break;
		case CTC_MODE:
			CLR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
		case FAST_PWM_MODE:
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
	}
}

void Timer0_SetCompareOutputMode (char Mode)
{
	if ((Mode >= 0) && (Mode <=3))
	{
		TCCR0 &= ~(0b11<< COM00);
		TCCR0 |= (Mode << COM00);
	}
}

void Timer0_SetClkPrescaler (char Prescale)
{
	if ((Prescale >= 0) && (Prescale <= 7))
	{
		TCCR0 &= ~(0b111 << CS00);
		TCCR0 |= (Prescale << CS00);
	}
}

void Timer0_SetTCNT (char TCNT_Value)
{
	TCNT0 = TCNT_Value;
}
void Timer0_SetOCR (char OCR_Value)
{
	OCR0 = OCR_Value;
}

void Timer0_EnableOverflowInterrupt()
{
	SET_BIT(TIMSK, TOIE0);
}
void Timer0_DisableOverflowInterrupt()
{
	CLR_BIT(TIMSK, TOIE0);
}

void Timer0_EnableCompareInterrupt()
{
	SET_BIT(TIMSK, OCIE0);
}
void Timer0_DisableCompareInterrupt()
{
	CLR_BIT(TIMSK, OCIE0);
}

char Timer0_CheckOverflow()
{
	return GET_BIT(TIFR, TOV0);
}

void Timer0_InitPWM(void)
{
	Timer0_SetMode(PWM_MODE);
	Timer0_SetCompareOutputMode(CLEAR_MODE);
	Timer0_EnableOverflowInterrupt();
	Timer0_SetOCR(20);
	Timer0_SetClkPrescaler(CLKBY1024);
}

void Timer0_InitNormal(void)
{
	Timer0_SetMode(NORMAL_MODE);
	Timer0_SetCompareOutputMode(NORMAL_PORT);
	Timer0_EnableOverflowInterrupt();
	Timer0_SetClkPrescaler(CLKBY1024);
}




ISR(TIMER0_OVF_vect)
{
	static int Counter = 0;
	Counter++;
	if (Counter == 100)
	{
		TGL_BIT(PORTA, PA0);
		Counter = 0;
	}
}
