/*
 * BIT_Math.h
 *
 *  Created on: Oct 22, 2021
 *      Author: ALKODS
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT)	(REG|=(1<<BIT))
#define CLR_BIT(REG,BIT)	(REG&=~(1<<BIT))
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))
#define GET_BIT(REG,BIT)	((REG>>BIT)&(0x01))
#endif /* BIT_MATH_H_ */
