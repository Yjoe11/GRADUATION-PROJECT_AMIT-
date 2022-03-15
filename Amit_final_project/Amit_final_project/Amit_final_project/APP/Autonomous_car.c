/*
 * Fuck_Off.c
 *
 * Created: 3/11/2022 5:07:39 PM
 *  Author: alkods
 */ 

#include "Autonomous_car.h"

uint32 Right_Distance = 0;
uint32 Left_Distance = 0;
uint32 Tot_Distance = 0;
uint8 Obstacle_Detected = 0;
uint8 BackWard_move_active = 0;
SET_DEGREE Operation = No_Operation;

/*
	Function Name        : VEHICLE_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize HAL drivers that needed in the app 
						   and sent the orders to ultrasonic drivers.
*/

void VEHICLE_INIT (void)
{
	LCD_Init();
	LCD_Clear();
	DC_MOTOR_INIT();
	SERVO_MOTOR_INT();
	ULTRASONIC_INIT();
	ULTRASONIC_02_INIT();
	ULTRASONIC_ACTION_SET_CALLBACK(OBSTACLE_DETECTOR);
	ULTRASONIC_02_ACTION_SET_CALLBACK(BackWard_moving);
}

/*
	Function Name        : MOVE_FORWARD
	Function Returns     : void
	Function Arguments   : void
	Function Description : ORDER DC_MOTORS TO MOVE FORWARD.
*/

void MOVE_FORWARD (void)
{
	DC_MOTOR_DIRECTION(MOTOR_1, CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_2, CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_3, CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_4, CLOCK_WISE);
	LCD_Clear();
	LCD_WriteString("move forward");
	BackWard_move_active = 0 ;
}

/*
	Function Name        : VEHICLE_STOP
	Function Returns     : void
	Function Arguments   : void
	Function Description : ORDER DC_MOTORS TO STOP.
*/

void VEHICLE_STOP (void)
{
	DC_MOTOR_STOP();
} 

/*
	Function Name        : MOVE_BACKWARD
	Function Returns     : void
	Function Arguments   : void
	Function Description : ORDER DC_MOTORS TO MOVE BACKWARD.
*/

void MOVE_BACKWARD (void)
{
	DC_MOTOR_DIRECTION(MOTOR_1, ANTi_CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_2, ANTi_CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_3, ANTi_CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_4, ANTi_CLOCK_WISE);
	LCD_Clear();
	LCD_WriteString("move backward");
	BackWard_move_active = 1;
}

/*
	Function Name        : TURN_LEFT
	Function Returns     : void
	Function Arguments   : void
	Function Description : ORDER DC_MOTORS TO TURN THE VEHICAL LEFT.
*/

void TURN_LEFT (void)
{
	BackWard_move_active = 0 ;
	DC_MOTOR_DIRECTION(MOTOR_1, ANTi_CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_2, ANTi_CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_3, CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_4, CLOCK_WISE);
	LCD_Clear();
	LCD_WriteString("move LEFT");
	_delay_ms(300);
	MOVE_FORWARD();
	
}

/*
	Function Name        : TURN_RIGHT
	Function Returns     : void
	Function Arguments   : void
	Function Description : ORDER DC_MOTORS TO TURN THE VEHICAL RIGHT.
*/

void TURN_RIGHT (void)
{
	BackWard_move_active = 0 ;
	DC_MOTOR_DIRECTION(MOTOR_1, CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_2, CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_3, ANTi_CLOCK_WISE);
	DC_MOTOR_DIRECTION(MOTOR_4, ANTi_CLOCK_WISE);
	LCD_Clear();
	LCD_WriteString("move RIGHT");
	_delay_ms(300);
	MOVE_FORWARD();
	
}

/*
	Function Name        : TURN_LEFT
	Function Returns     : void
	Function Arguments   : uint32 Distance
	Function Description : take the value of the distance that returned from the ultrasonic and operate the vechicle by controling the servo 
						   to collect the data from the servo degrees then sent the order to dc to avoid the obstecal if it is detected.
						   if the opsecal has detected about 20 cm the vehcal stops and collect the data
						   from each degree and if the distance of total degree is smaller than 100 cm 
						   the vehcle will move backward until their an avilabel space around the car and turn the car to the suitable direction
*/

void OBSTACLE_DETECTOR (uint32 Distance)
{
	if (!Obstacle_Detected)
	{	if (Distance > 20)
		{
			MOVE_FORWARD();
		}
		else if (Distance <= 20)
		{
			Obstacle_Detected = 1;
			Operation = First_Right_Degree;
			VEHICLE_STOP();
			SERVO_MOTOR_START(5/*SET FIRST RIGHT DEGREE*/);
			LCD_Clear();
			LCD_GoTo(0, 5);
			LCD_WriteString("Opstacle");
			LCD_GoTo(1, 5);
			LCD_WriteString("Detected");
			_delay_ms(500);
		}
	}
	switch (Operation)
	{
	case First_Right_Degree:
		Right_Distance += Distance;
		SERVO_MOTOR_START(3/*SET LAST RIGHT DEGREE*/);
		_delay_ms(500);
		Operation = Last_Right_Degree;
		break;
	
	case Last_Right_Degree:
		Right_Distance += Distance;
		SERVO_MOTOR_START(11/*SET FIRST LEFT DEGREE*/);
		_delay_ms(500);
		Operation = First_Left_degree;
		break;
	
	case First_Left_degree:
		Left_Distance += Distance;
		SERVO_MOTOR_START(12/*SET LAST LEFT DEGREE*/);
		_delay_ms(500);
		Operation = Last_Left_Degree;
		break;
	
	case Last_Left_Degree:
		Left_Distance += Distance;
		Tot_Distance = Right_Distance + Left_Distance;
		if (Tot_Distance < 100)
		{
			MOVE_BACKWARD();
			SERVO_MOTOR_START(8/*SET initial DEGREE*/);
			_delay_ms(500);
			Operation = First_Right_Degree;
		}
		else
		{
			if (Right_Distance > Left_Distance)
			{
				SERVO_MOTOR_START(8/*SET initial DEGREE*/);
				TURN_RIGHT();
				_delay_ms(500);
				
				Obstacle_Detected = 0;
				Tot_Distance = 0;
				Left_Distance = 0;
				Right_Distance = 0;
				Operation = No_Operation;
			} 
			else
			{
				
				SERVO_MOTOR_START(8/*SET initial DEGREE*/);
				TURN_LEFT();
				_delay_ms(500);
				Obstacle_Detected = 0;
				Tot_Distance = 0;
				Left_Distance = 0;
				Right_Distance = 0;
				Operation = No_Operation;
			}
		}
		break;
	default:
		break;
		
	}
}

/*
	Function Name        : VEHICLE_MANEGMENT
	Function Returns     : void
	Function Arguments   : void
	Function Description : operating the car by sending pulse to the ultrasonic sensors.
*/

void VEHICLE_MANEGMENT (void)
{
	ULTRASONIC_TREGGIER();
	ULTRASONIC_02_TREGGIER();
}

/*
	Function Name        : BackWard_moving
	Function Returns     : void
	Function Arguments   : uint32 Distance
	Function Description : if the motor is moving backward the back sesor working on detection the obstacle 
						   and if the obsacle detected about 20 cm the direction of moving will be reversed.
*/

void BackWard_moving(uint32 Distance)
{
	if (BackWard_move_active)
	{
		if (Distance < 20)
		{
			MOVE_FORWARD();
		}
	}
}