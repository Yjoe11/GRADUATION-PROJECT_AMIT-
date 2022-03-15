/*
 * ULTRASONIC.c
 *
 * Created: 3/9/2022 5:14:25 PM
 *  Author: alkods
 */ 


#include "ULTRASONIC_02.h"


uint8 SENSOR_02_TRIGGERED = 0 ;
uint8 STARTING_02_PULSE = 0 ;
uint8 TIMER_COUNTER_02 = 0 ;

uint32 DISTANCE_02 = 0;


void (*CALLBACK_PTR_ult_02) (uint32 val) = 0;

/*
	Function Name        : ULTRASONIC_02_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize ultrasonic
*/

void ULTRASONIC_02_INIT(void)
{
	
	DIO_SetPinDir(TRIGGER_PORT, TRIGGER, DIO_PIN_OUTPUT);
	
	DIO_SetPinDir(ECHO_PORT, ECHO, DIO_PIN_INPUT);
	
	SET_PULL_UP_RESESTOR(ECHO_PORT, ECHO);
	EXTERNAL_INT1_INIT();
	TIMER_0_INIT();
	EXTERNAL_INIT1_SET_CALLBACK(ULTRASONIC_02_EXT_INT);
	TIMER_0_INIT_SET_CALLBACK(ULTRASONIC_02_OVF_INT);
}


/*
	Function Name        : ULTRASONIC_02_TREGGIER
	Function Returns     : void
	Function Arguments   : void
	Function Description : sent pulse to trigger the ultrasonic sensor
*/
void ULTRASONIC_02_TREGGIER(void)
{
	if (!SENSOR_02_TRIGGERED)
	{
		
		DIO_SetPinVal(TRIGGER_PORT, TRIGGER, DIO_PIN_HIGH);
		_delay_us(10);
		
		DIO_SetPinVal(TRIGGER_PORT, TRIGGER, DIO_PIN_LOW);
		SENSOR_02_TRIGGERED = 1 ;
	}
}


/*
	Function Name        : ULTRASONIC_02_ACTION_SET_CALLBACK
	Function Returns     : void
	Function Arguments   : void (*COPY_FUNCTION) (uint32 DISTANCE)
	Function Description : pass the address of the function of upper layer to perform in this layer
*/
void ULTRASONIC_02_ACTION_SET_CALLBACK( void (*COPY_FUNCTION) (uint32 DISTANCE))
{
	CALLBACK_PTR_ult_02 = COPY_FUNCTION;
	
}

/*
	Function Name        : ULTRASONIC_02_EXT_INT
	Function Returns     : void
	Function Arguments   : void
	Function Description : this function will be sent to isr of ext inturrpt to perform it when trigger the sensor
*/

void ULTRASONIC_02_EXT_INT(void)
{
	//LCD_WriteString("CM");
	if (SENSOR_02_TRIGGERED == 1)
	{
		if (STARTING_02_PULSE == 0)
		{
			TIMER_0_START();
			TCNT0 = 0x00;
			STARTING_02_PULSE = 1;
			TIMER_COUNTER_02 = 0;
		}
		else
		{
			DISTANCE_02 = ((TIMER_COUNTER_02 * 256) + TCNT0) * (64 / 58);
			if(CALLBACK_PTR_ult_02 != 0)
			{
				CALLBACK_PTR_ult_02(DISTANCE_02);
			}
			_delay_us(5);
			TCNT0 = 0x00 ;
			STARTING_02_PULSE = 0;
			TIMER_COUNTER_02 = 0;
			SENSOR_02_TRIGGERED = 0;
		}
	}
}
/*
	Function Name        : ULTRASONIC_02_OVF_INT
	Function Returns     : void
	Function Arguments   : void
	Function Description : this function will be sent to isr of ovf inturrpt to perform it when trigger the sensor
*/
void ULTRASONIC_02_OVF_INT(void)
{
	TIMER_COUNTER_02++;
	//LCD_WriteString("CM");
	if (TIMER_COUNTER_02 > 362)
	{
		TIMER_0_STOP() ;
		TCNT0 = 0x00 ;
		SENSOR_02_TRIGGERED = 0;
		STARTING_02_PULSE = 0;
		TIMER_COUNTER_02 = 0;
	}
}



