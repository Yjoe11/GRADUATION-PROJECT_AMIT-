/*
 * ULTRASONIC.c
 *
 * Created: 3/9/2022 5:14:25 PM
 *  Author: alkods
 */ 


#include "ULTRASONIC.h"


uint8 SENSOR_TRIGGERED = 0 ;
uint8 STARTING_PULSE = 0 ;
uint8 TIMER_COUNTER = 0 ;

uint32 DISTANCE = 0;


void (*CALLBACK_PTR_ult) (uint32 val) = 0;

/*
	Function Name        : ULTRASONIC_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize ultrasonic
*/

void ULTRASONIC_INIT(void)
{
	
	DIO_SetPinDir(TRIGGER_PORT, TRIGGER, DIO_PIN_OUTPUT);

	DIO_SetPinDir(ECHO_PORT, ECHO, DIO_PIN_INPUT);

	SET_PULL_UP_RESESTOR(ECHO_PORT, ECHO);
	EXTERNAL_INT0_INIT();
	TIMER_2_INIT();
	EXTERNAL_INIT0_SET_CALLBACK(ULTRASONIC_EXT_INT);
	TIMER_2_INIT_SET_CALLBACK(ULTRASONIC_OVF_INT);
}
/*
	Function Name        : ULTRASONIC_TREGGIER
	Function Returns     : void
	Function Arguments   : void
	Function Description : sent pulse to trigger the ultrasonic sensor
*/
void ULTRASONIC_TREGGIER(void)
{
	if (!SENSOR_TRIGGERED)
	{
		DIO_SetPinVal(TRIGGER_PORT, TRIGGER, DIO_PIN_HIGH);
		_delay_us(10);
		DIO_SetPinVal(TRIGGER_PORT, TRIGGER, DIO_PIN_LOW);
		SENSOR_TRIGGERED = 1 ;
	}
}
/*
	Function Name        : ULTRASONIC_ACTION_SET_CALLBACK
	Function Returns     : void
	Function Arguments   : void (*COPY_FUNCTION) (uint32 DISTANCE)
	Function Description : pass the address of the function of upper layer to perform in this layer
*/
void ULTRASONIC_ACTION_SET_CALLBACK( void (*COPY_FUNCTION) (uint32 DISTANCE))
{
	CALLBACK_PTR_ult = COPY_FUNCTION;
	
}
/*
	Function Name        : ULTRASONIC_EXT_INT
	Function Returns     : void
	Function Arguments   : void
	Function Description : this function will be sent to isr of ext inturrpt to perform it when trigger the sensor
*/
void ULTRASONIC_EXT_INT(void)
{
	//LCD_WriteString("CM");
	if (SENSOR_TRIGGERED == 1)
	{
		if (STARTING_PULSE == 0)
		{
			TIMER_2_START();
			TCNT2 = 0x00;
			STARTING_PULSE = 1;
			TIMER_COUNTER = 0;
		}
		else
		{
			DISTANCE = ((TIMER_COUNTER * 256) + TCNT2) * (64 / 58);
			if(CALLBACK_PTR_ult != 0)
			{
				CALLBACK_PTR_ult(DISTANCE);
			}
			_delay_us(5);
			TCNT2 = 0x00 ;
			STARTING_PULSE = 0;
			TIMER_COUNTER = 0;
			SENSOR_TRIGGERED = 0;
		}
	}
}
/*
	Function Name        : ULTRASONIC_OVF_INT
	Function Returns     : void
	Function Arguments   : void
	Function Description : this function will be sent to isr of ovf inturrpt to perform it when trigger the sensor
*/
void ULTRASONIC_OVF_INT(void)
{
	TIMER_COUNTER++;
	//LCD_WriteString("CM");
	if (TIMER_COUNTER > 362)
	{
		TIMER_2_STOP() ;
		TCNT2 = 0x00 ;
		SENSOR_TRIGGERED = 0;
		STARTING_PULSE = 0;
		TIMER_COUNTER = 0;
	}
}



