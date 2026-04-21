/*
 * UART_Interface.h
 *
 *  Created on: ١٨‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include <avr/io.h>
#include "BIT_LIB.h"
char UART_GetReceiveFlag(void);
char UART_GetTransmitFlag(void);
char UART_CheckDataRegisterEmpty(void);
/*
 * RXCIE | TXCIE | UDRIE
 */
void UART_SetInterruptStates(char State);

void UART_EnableReceiver(void);

void UART_EnableTransmitter(void);

typedef enum {FIVE_BITS, SIX_BITS, SEVEN_BITS, EIGHT_BITS, NINE_BITS=7} DataSize_e;
void UART_SetDataSize(DataSize_e Size);

typedef enum {DISABLED, RESERVED, EVEN_PARITY, ODD_PARITY} ParityMode_e;
void UART_SetParityMode(ParityMode_e Mode);

typedef enum {ONE_BIT, TWO_BITS} StopBits_e;
void UART_SetStopBit(StopBits_e Mode);

void UART_SetBaudRate(int Baud);
void UART_SendData (char Data);
char UART_ReadData (void);

void UART_Init(void);

#endif /* UART_INTERFACE_H_ */
