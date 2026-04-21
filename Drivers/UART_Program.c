/*
 * UART_Program.c
 *
 *  Created on: ١٨‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */


#include "UART_Interface.h"


char UART_GetReceiveFlag(void)
{
	return GET_BIT(UCSRA, RXC);
}
char UART_GetTransmitFlag(void)
{
	return GET_BIT(UCSRA, TXC);
}
char UART_CheckDataRegisterEmpty(void)
{
	return GET_BIT(UCSRA, UDRE);
}

void UART_SetInterruptStates(char State)
{
	if ((State >= 0) && (State <= 7))
	{
		UCSRB &= ~(0b111 << UDRIE);
		UCSRB |= (State<< UDRIE);
	}
}

void UART_EnableReceiver(void)
{
	SET_BIT(UCSRB, RXEN);
}

void UART_EnableTransmitter(void)
{
	SET_BIT(UCSRB, TXEN);
}

void UART_SetDataSize(DataSize_e Size)
{
	if ((Size >= 0) && (Size <= 7))
	{
		UCSRB &= ~(0b1 << UCSZ2);
		UCSRB |= (GET_BIT(Size, 2) << UCSZ2);
		SET_BIT(UCSRC, URSEL);
		UCSRC &= ~(0b11 << UCSZ0);
		UCSRC |= ((Size&0b11) << UCSZ0);
	}
}

void UART_SetParityMode(ParityMode_e Mode)
{
	if ((Mode >= 0) && (Mode <= 3))
	{
		SET_BIT(UCSRC, URSEL);
		UCSRC &= ~(0b11 << UPM0);
		UCSRC |= (Mode << UPM0);
	}
}

void UART_SetStopBit(StopBits_e Mode)
{
	SET_BIT(UCSRC, URSEL);
	UCSRC &= ~(0b1 << USBS);
	UCSRC |= (GET_BIT(Mode, 0) << USBS);
}

void UART_SetBaudRate(int Baud)
{
	UBRRL = (char)Baud;
	UBRRH = (char)((Baud >> 8)&(0x0f));
}

void UART_SendData (char Data)
{
	while (!GET_BIT(UCSRA, UDRE));
	UDR = Data;
	while (!GET_BIT(UCSRA, TXC));
}
char UART_ReadData (void)
{
	while (!GET_BIT(UCSRA, RXC));
	return UDR;
}

void UART_Init(void)
{
	UART_SetInterruptStates(0b000);
	UART_SetDataSize(EIGHT_BITS);
	UART_SetParityMode(DISABLED);
	UART_SetStopBit(ONE_BIT);
	UART_SetBaudRate(51);
	UART_EnableReceiver();
	UART_EnableTransmitter();
}
