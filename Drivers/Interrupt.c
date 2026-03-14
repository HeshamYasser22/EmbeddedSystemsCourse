/*
 * Program.c
 *
 *  Created on: ١٤‏/٠٣‏/٢٠٢٦
 *      Author: Hesha
 */


#define F_CPU     8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LOWLEVEL    0
#define ANYCHANGE   1
#define FALLINGEDGE 2
#define RISINGEDGE  3

#define INT0		0
#define INT1		1
#define INT2		2

#define SET_BIT(Reg, Bit)      Reg|=(1<<Bit)
#define CLR_BIT(Reg, Bit)      Reg&=~(1<<Bit)
#define GET_BIT(Reg, Bit)      ((Reg>>Bit)&1)
#define TGL_BIT(Reg, Bit)      Reg^=(1<<Bit)

void SetINTPinPullUp(char Pin);

void SetINTEvent(char Pin, char EventType);
void EnablePinInterrupt(char Pin);
void EnableGlobalInterrupt ();
void DisableGlobalInterrupt ();


int main ()
{
	SET_BIT(DDRA, 0);
	SET_BIT(PORTA, 0);
	SET_BIT(DDRA, 1);
	SET_BIT(PORTA, 1);
	SetINTPinPullUp(INT0);
	SetINTEvent(INT0, FALLINGEDGE);
	EnablePinInterrupt(INT0);
	EnableGlobalInterrupt();
	while (1)
	{
		TGL_BIT(PORTA, 1);
		_delay_ms(1000);
	}
}

void SetINTPinPullUp(char Pin)
{
	switch (Pin)
	{
	case INT0:
		CLR_BIT(DDRD, 2);
		SET_BIT(PORTD, 2);
		break;
	case INT1:
		CLR_BIT(DDRD, 3);
		SET_BIT(PORTD, 3);
		break;
	case INT2:
		CLR_BIT(DDRB, 2);
		SET_BIT(PORTB, 2);
		break;
	}

}

void SetINTEvent(char Pin, char EventType)
{
	switch (Pin)
	{
	case INT0:
		switch (EventType)
		{
		case LOWLEVEL:
			CLR_BIT(MCUCR, 0);
			CLR_BIT(MCUCR, 1);
			break;
		case ANYCHANGE:
			SET_BIT(MCUCR, 0);
			CLR_BIT(MCUCR, 1);
			break;
		case FALLINGEDGE:
			CLR_BIT(MCUCR, 0);
			SET_BIT(MCUCR, 1);
			break;
		case RISINGEDGE:
			SET_BIT(MCUCR, 0);
			SET_BIT(MCUCR, 1);
			break;
		default:
			CLR_BIT(MCUCR, 0);
			CLR_BIT(MCUCR, 1);
			break;
		}
		break;
	case INT1:
		switch (EventType)
		{
		case LOWLEVEL:
			CLR_BIT(MCUCR, 2);
			CLR_BIT(MCUCR, 3);
			break;
		case ANYCHANGE:
			SET_BIT(MCUCR, 2);
			CLR_BIT(MCUCR, 3);
			break;
		case FALLINGEDGE:
			CLR_BIT(MCUCR, 2);
			SET_BIT(MCUCR, 3);
			break;
		case RISINGEDGE:
			SET_BIT(MCUCR, 2);
			SET_BIT(MCUCR, 3);
			break;
		default:
			CLR_BIT(MCUCR, 2);
			CLR_BIT(MCUCR, 3);
			break;
		}
			break;
	}

}

void EnablePinInterrupt(char Pin)
{
	switch (Pin)
	{
	case INT0:
		SET_BIT(GICR, 6);
		break;
	case INT1:
		SET_BIT(GICR, 7);
		break;
	case INT2:
		SET_BIT(GICR, 5);
		break;
	default:
		break;
	}
}

void EnableGlobalInterrupt ()
{
	SET_BIT(SREG, 7);
}

void DisableGlobalInterrupt ()
{
	CLR_BIT(SREG, 7);
}



ISR(INT0_vect)
{
	TGL_BIT(PORTA, 0);
}
