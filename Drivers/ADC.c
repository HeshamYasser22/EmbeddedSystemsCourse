/*
 * Program.c
 *
 *  Created on: ٢١‏/٠٣‏/٢٠٢٦
 *      Author: Hesham
 */



#define F_CPU     8000000UL
#include <avr/io.h>



#define SET_BIT(Reg, Bit)      Reg|=(1<<Bit)
#define CLR_BIT(Reg, Bit)      Reg&=~(1<<Bit)
#define GET_BIT(Reg, Bit)      ((Reg>>Bit)&1)
#define TGL_BIT(Reg, Bit)      Reg^=(1<<Bit)



int GetADCValue();
float ConvertToAnalog(int DigitalValue);
void SetADCChannel(char Channel);
void ADCInit();
void EnableADC();
void EnableADCInterrupt();
void DisableADCInterrupt();
void StartADC();
char CheckADCEndOfConversion();

int main ()
{
	int Dig_Value;
	float Analog_Value;
	SET_BIT(DDRA, 1);
	CLR_BIT(PORTA, 1);
	SetADCChannel(0);
	ADCInit();
	EnableADC();
	while (1)
	{
		StartADC();
		while (!CheckADCEndOfConversion());
		Dig_Value = GetADCValue();
		Analog_Value = ConvertToAnalog(Dig_Value);
		if (Analog_Value >= 2.5)
		{
			SET_BIT(PORTA, 1);
		}
		else
		{
			CLR_BIT(PORTA, 1);
		}
	}
}

int GetADCValue()
{
	return ADC;
}

void SetADCChannel(char Channel)
{
	ADMUX &=  ~(0b11111 << MUX0);
	ADMUX |=  (Channel << MUX0);
	CLR_BIT(DDRA, Channel);
	CLR_BIT(PORTA, Channel);
}

void ADCInit()
{
	CLR_BIT(ADMUX, ADLAR);
	ADMUX &=  ~(0b11 << REFS0);
	ADCSRA &=  ~(0b111 << ADPS0);
}

void EnableADC()
{
	SET_BIT(ADCSRA, ADEN);
}

void EnableADCInterrupt()
{
	SET_BIT(ADCSRA, ADIE);
}

void DisableADCInterrupt()
{
	CLR_BIT(ADCSRA, ADIE);
}

void StartADC ()
{
	SET_BIT(ADCSRA, ADSC);
}

char CheckADCEndOfConversion()
{
	if (GET_BIT(ADCSRA, ADIF))
	{
		SET_BIT(ADCSRA, ADIF);
		return 1;
	}
	else
	{
		return 0;
	}
}
float ConvertToAnalog(int DigitalValue)
{
	return (DigitalValue/1024.0)*5;
}
