/*
 * SERVO_MOTOR.h
 *
 * Created: 06-Mar-22 2:31:26 AM
 *  Author: JOE
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_

#include "SERVO_MOTOR_(CONFG).h"
#include "../../MCAL/TIMER_1/TIMER_1.h"
#include "../../MCAL/DIO/DIO.h"


void SERVO_MOTOR_INT (void);

void SERVO_MOTOR_START(uint8 DUTY_CYCLE); 







#endif /* SERVO_MOTOR_H_ */