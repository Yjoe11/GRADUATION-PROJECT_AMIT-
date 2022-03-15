/*
 * SERVO_MOTOR.c
 *
 * Created: 06-Mar-22 2:31:08 AM
 *  Author: JOE
 */ 


#include "SERVO_MOTOR.h"

/*
	Function Name        : SERVO_MOTOR_INT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize servo motor
*/
void SERVO_MOTOR_INT (void)
{
	// FIRST SETTING THE DIO_PIN NEEDED FOR THE OCR 
	
	
	// SECOND CALLING THE PMW_INT FUCTION 
	DIO_SetPinDir(SERVO_PORT, SERVO_PIN, DIO_PIN_OUTPUT);	
	TIMER_1_INIT();
	//SET_BIT(DDRD, 5);
	//SERVO_MOTOR_START(5);
	// THIRD CALLING THE PWM_START FUCTION 
	
	TIMER_1_START();
	SERVO_MOTOR_START(8);
	
}

/*
	Function Name        : SERVO_MOTOR_START
	Function Returns     : void
	Function Arguments   : DUTY_CYCLE
	Function Description : set the servo by taking the valye of the duty cycle
*/

void SERVO_MOTOR_START( uint8 DUTY_CYCLE) // AT THE DUTY_CYCLE IN ORDER TO SELECT THE ANGLE FOR THE SERVO 
{
	TIMER_1_SET_DUTY_CYCLE(DUTY_CYCLE);
}