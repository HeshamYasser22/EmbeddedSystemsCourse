/*
 * BIT_LIB.h
 *
 *  Created on: ٠٧‏/٠٤‏/٢٠٢٦
 *      Author: Hesha
 */

#ifndef BIT_LIB_H_
#define BIT_LIB_H_

#define SET_BIT(Reg, Bit) 	Reg|=(1<<Bit)
#define CLR_BIT(Reg, Bit) 	Reg&=~(1<<Bit)
#define TGL_BIT(Reg, Bit) 	Reg^=(1<<Bit)
#define GET_BIT(Reg, Bit) 	((Reg>>Bit)&1)


#endif /* BIT_LIB_H_ */
