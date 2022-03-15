/*
 * DC_MOTOR.h
 *
 * Created: 3/4/2022 7:57:37 PM
 *  Author: alkods
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMER_0/TIMER_0.h"
#include "DC_MOTOR_CONFIGURATION.h"

#define  CLOCK_WISE			0
#define  ANTi_CLOCK_WISE	1

#define  MOTOR_1			1
#define  MOTOR_2			2
#define  MOTOR_3			3
#define  MOTOR_4			4


void DC_MOTOR_INIT(void);

void DC_MOTOR_DIRECTION(uint8 MOTOR, uint8 DIRECTION);

void DC_MOTOR_START(void);

void DC_MOTOR_STOP(void);

void DC_MOTOR_SPEED(uint8 SPEED);



#endif /* DC_MOTOR_H_ */