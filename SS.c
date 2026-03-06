/*
 * Program.c
 *
 *  Created on: ٢٨‏/٠٢‏/٢٠٢٦
 *      Author: Hesha
 */

#define F_CPU      8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SS_PORT    PORTC
#define SS_DDR     DDRC

void SS_Init(void);
void SS_ShowNum(int Num);


char SS_ARR[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void main (void)
{

	SS_Init();
	while (1)
	{
		for (int i = 0; i < 10; i++)
		{
			SS_ShowNum(i);
			_delay_ms(1000);
		}
	}
}

void SS_Init(void)
{
	SS_DDR = 0xff;
	SS_PORT = 0;
}

void SS_ShowNum(int Num)
{
	if (Num <= 9)
	{
		SS_PORT = SS_ARR[Num];
	}
}
