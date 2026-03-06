/*
 * Program.c
 *
 *  Created on: ٢٧‏/٠٢‏/٢٠٢٦
 *      Author: Hesha
 */

#define F_CPU	8000000UL
#include <avr/io.h>
#include <util/delay.h>

void KeyPad_Init(void);
char Get_Pressed (void);

#define KEYPAD_PORT    PORTA
#define KEYPAD_DDR     DDRA
#define KEYPAD_PIN     PINA

int Row_Pins[] = {0,1,2,3};

int Col_Pins[] = {4,5,6,7};


#define ROW_NUM		4
#define COL_NUM		4

char Keys [ROW_NUM][COL_NUM] = {{'7','8','9','/'}, {'4','5','6','*'}, {'1','2','3','-'}, {'O', '0', '=', '+'}};

#define SET_BIT(Reg, Bit)     Reg|=(1<<Bit)
#define CLR_BIT(Reg, Bit)     Reg&=~(1<<Bit)
#define GET_BIT(Reg, Bit)     ((Reg>>Bit)&1)
#define TGL_BIT(Reg, Bit)     Reg^=(1<<Bit)



void main (void)
{
	SET_BIT(DDRB, 1);
	CLR_BIT(PORTB, 1);

	KeyPad_Init();
	while (1)
	{
		if (Get_Pressed() == '1')
		{
			TGL_BIT(PORTB, 1);
		}

	}

}


void KeyPad_Init(void)
{
	for (int i = 0; i < 4; i++)
	{
		SET_BIT(KEYPAD_DDR, Row_Pins[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		CLR_BIT(KEYPAD_DDR, Col_Pins[i]);
		SET_BIT(KEYPAD_PORT, Col_Pins[i]);
	}
}

char Get_Pressed (void)
{
	int Getted;
	while (1)
	{
		for (int i = 0; i < ROW_NUM; i++)
		{
			SET_BIT(KEYPAD_PORT, Row_Pins[0]);
			SET_BIT(KEYPAD_PORT, Row_Pins[1]);
			SET_BIT(KEYPAD_PORT, Row_Pins[2]);
			SET_BIT(KEYPAD_PORT, Row_Pins[3]);
			CLR_BIT(KEYPAD_PORT, Row_Pins[i]);
			for (int j = 0; j < COL_NUM; j++)
			{
				Getted = GET_BIT(KEYPAD_PIN, Col_Pins[j]);
				if (Getted == 0)
				{
					_delay_ms(15);
					Getted = GET_BIT(KEYPAD_PIN, Col_Pins[j]);
					if (Getted == 0)
					{
						return Keys[i][j];
					}
				}
			}
		}
	}

}



