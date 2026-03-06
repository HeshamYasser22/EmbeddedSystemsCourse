/*
 * Program.c
 *
 *  Created on: ٠٥‏/٠٣‏/٢٠٢٦
 *      Author: Hesha
 */

typedef unsigned char uint8;
#define F_CPU 	8000000UL

#include <avr/io.h>
#include <util/delay.h>



void LCD_Init(void);
void LCD_SendCmd(uint8 Cmd);
void LCD_SendData(uint8 Data);
void LCD_SendString(uint8 * Ptr, uint8 size);
void LCD_ClearDisplay();
void LCD_SetRowCol (uint8 Row, uint8 Col);

#define LCD_DATA_PORT	PORTA
#define LCD_DATA_DDR	DDRA
#define LCD_CTRL_PORT   PORTB
#define LCD_CTRL_DDR    DDRB
#define LCD_RW			0
#define LCD_RS			1
#define LCD_EN			2

#define SET_BIT(Reg, Bit)		Reg |= (1<< Bit)
#define CLR_BIT(Reg, Bit)		Reg &= ~(1<< Bit)
#define GET_BIT(Reg, Bit)		((Reg>>Bit) & 1)
#define TGL_BIT(Reg, Bit)       Reg ^= (1<< Bit)



uint8 Name [] = "Embedded";

void main (void)
{
	LCD_Init();
	while (1)
	{
		LCD_SetRowCol(1,2);
		LCD_SendString(Name, sizeof(Name));
		_delay_ms(1000);
	}
}



void LCD_Init(void)
{
	LCD_DATA_PORT = 0x0;
	LCD_DATA_DDR = 0xff;        //0b11111111
	SET_BIT(LCD_CTRL_DDR, LCD_RW);  // RW OUT
	SET_BIT(LCD_CTRL_DDR, LCD_RS);  // RS OUT
	SET_BIT(LCD_CTRL_DDR, LCD_EN);  // EN OUT
	LCD_SendCmd(0b00111000);
	LCD_SendCmd(0b00001100);
	LCD_SendCmd(0b00000001);
	LCD_SendCmd(0b00000110);
}
void LCD_SendCmd(uint8 Cmd)
{
	CLR_BIT(LCD_CTRL_PORT, LCD_RW);
	CLR_BIT(LCD_CTRL_PORT, LCD_RS);
	LCD_DATA_PORT = Cmd;
	SET_BIT(LCD_CTRL_PORT, LCD_EN);
	_delay_us(1);
	CLR_BIT(LCD_CTRL_PORT, LCD_EN);
	_delay_ms(2);
}
void LCD_SendData(uint8 Data)
{
	CLR_BIT(LCD_CTRL_PORT, LCD_RW);
	SET_BIT(LCD_CTRL_PORT, LCD_RS);
	LCD_DATA_PORT = Data;
	SET_BIT(LCD_CTRL_PORT, LCD_EN);
	_delay_us(1);
	CLR_BIT(LCD_CTRL_PORT, LCD_EN);
	_delay_ms(2);
}


void LCD_SendString(uint8 Ptr[], uint8 size)
{
	for (int i = 0; i < size; i++)
	{
		LCD_SendData(Ptr[i]);
	}
}

void LCD_ClearDisplay()
{
	LCD_SendCmd(1);
}

void LCD_SetRowCol (uint8 Row, uint8 Col)
{
	uint8 ADD = (Row*0x40) + Col;
	SET_BIT (ADD, 7);
	LCD_SendCmd (ADD);
}
