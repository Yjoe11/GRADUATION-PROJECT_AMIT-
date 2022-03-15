/*
 * Fuck_Off.h
 *
 * Created: 3/11/2022 4:59:35 PM
 *  Author: alkods
 */ 


#ifndef Autonomous_car_H_
#define Autonomous_car_H_


#include "../HAL/ULTRASONIC/ULTRASONIC.h"
#include "../HAL/ULTRASONIC_02/ULTRASONIC_02.h"
#include "../HAL/DC_MOTOR/DC_MOTOR.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/SERVO/SERVO_MOTOR.h"
#include "Autonomous_car_configuration.h"

void VEHICLE_INIT(void);

void MOVE_FORWARD(void);

void VEHICLE_STOP(void);

void MOVE_BACKWARD(void);

void TURN_RIGHT(void);

void TURN_LEFT(void);

void OBSTACLE_DETECTOR(uint32 Distance);

void VEHICLE_MANEGMENT(void);

void lulu(void);

void BackWard_moving(uint32 Distance);

#endif 