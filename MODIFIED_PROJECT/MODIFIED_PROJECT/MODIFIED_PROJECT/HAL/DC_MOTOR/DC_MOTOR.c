/*
 * DC_MOTOR.c
 *
 * Created: 3/4/2022 8:44:49 PM
 *  Author: alkods
 */ 


#include "DC_MOTOR.h"

void DC_MOTOR_INIT(void)
{
	DIO_SetPinDir(IN_11_PORT, IN_11, DIO_PIN_OUTPUT);
	DIO_SetPinDir(IN_12_PORT, IN_12, DIO_PIN_OUTPUT);
	DIO_SetPinDir(IN_21_PORT, IN_21, DIO_PIN_OUTPUT);
	DIO_SetPinDir(IN_22_PORT, IN_22, DIO_PIN_OUTPUT);
	DIO_SetPinDir(IN_31_PORT, IN_31, DIO_PIN_OUTPUT);
	DIO_SetPinDir(IN_32_PORT, IN_32, DIO_PIN_OUTPUT);
	DIO_SetPinDir(IN_41_PORT, IN_41, DIO_PIN_OUTPUT);
	DIO_SetPinDir(IN_42_PORT, IN_42, DIO_PIN_OUTPUT);
	//TIMER_0_INIT();
}

void DC_MOTOR_DIRECTION(uint8 MOTOR_NUM, uint8 DIRECTION)
{
	switch (DIRECTION)
	{
		case CLOCK_WISE:
			switch (MOTOR_NUM)
			{
				case MOTOR_1:
					DIO_SetPinVal(IN_11_PORT , IN_11 , DIO_PIN_HIGH);
					DIO_SetPinVal(IN_12_PORT , IN_12 , DIO_PIN_LOW);
					break;
				case MOTOR_2:
					DIO_SetPinVal(IN_21_PORT , IN_21 , DIO_PIN_HIGH);
					DIO_SetPinVal(IN_22_PORT , IN_22 , DIO_PIN_LOW);
					break;
				case MOTOR_3:
					DIO_SetPinVal(IN_31_PORT , IN_31 , DIO_PIN_HIGH);
					DIO_SetPinVal(IN_32_PORT , IN_32 , DIO_PIN_LOW);
					break;
				case MOTOR_4:
					DIO_SetPinVal(IN_41_PORT , IN_41 , DIO_PIN_HIGH);
					DIO_SetPinVal(IN_42_PORT , IN_42 , DIO_PIN_LOW);
					break;
				default:
					break;
			}
			break;
		case ANTi_CLOCK_WISE:
			switch (MOTOR_NUM)
			{
				case MOTOR_1:
					DIO_SetPinVal(IN_11_PORT , IN_11 , DIO_PIN_LOW);
					DIO_SetPinVal(IN_12_PORT , IN_12 , DIO_PIN_HIGH);
					break;
				case MOTOR_2:
					DIO_SetPinVal(IN_21_PORT , IN_21 , DIO_PIN_LOW);
					DIO_SetPinVal(IN_22_PORT , IN_22 , DIO_PIN_HIGH);
					break;
				case MOTOR_3:
					DIO_SetPinVal(IN_31_PORT , IN_31 , DIO_PIN_LOW);
					DIO_SetPinVal(IN_32_PORT , IN_32 , DIO_PIN_HIGH);
					break;
				case MOTOR_4:
					DIO_SetPinVal(IN_41_PORT , IN_41 , DIO_PIN_LOW);
					DIO_SetPinVal(IN_42_PORT , IN_42 , DIO_PIN_HIGH);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void DC_MOTOR_START(void)
{
	TIMER_0_START();
}

void DC_MOTOR_STOP(void)
{
	DIO_SetPinVal(IN_11_PORT , IN_11 , DIO_PIN_HIGH);
	DIO_SetPinVal(IN_12_PORT , IN_12 , DIO_PIN_HIGH);
	DIO_SetPinVal(IN_21_PORT , IN_21 , DIO_PIN_HIGH);
	DIO_SetPinVal(IN_22_PORT , IN_22 , DIO_PIN_HIGH);
	DIO_SetPinVal(IN_31_PORT , IN_31 , DIO_PIN_HIGH);
	DIO_SetPinVal(IN_32_PORT , IN_32 , DIO_PIN_HIGH);
	DIO_SetPinVal(IN_41_PORT , IN_41 , DIO_PIN_HIGH);
	DIO_SetPinVal(IN_42_PORT , IN_42 , DIO_PIN_HIGH);
}

void DC_MOTOR_SPEED(uint8 SPEED)
{
	SPEED*=10;
	TIMER_0_PWM_SET_DUTY_CYCLE(SPEED);
}
