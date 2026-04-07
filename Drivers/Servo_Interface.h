/*
 * Servo_Interface.h
 *
 *  Created on: ٠٨‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */

#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_

#include "Timer1_Interface.h"
#include "BIT_LIB.h"

void Servo_Init(void);

void Servo_SendAngle(char Angle);

#endif /* SERVO_INTERFACE_H_ */
