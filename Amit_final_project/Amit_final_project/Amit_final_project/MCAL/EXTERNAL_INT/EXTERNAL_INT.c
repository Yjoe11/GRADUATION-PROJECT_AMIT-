/*
 * EXTERNAL_INT.c
 *
 * Created: 2/13/2022 5:17:05 PM
 *  Author: alkods
 */ 


#include "EXTERNAL_INT.h"

/*
	Function Name        : SET_GLOBAL_INT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Activate global int
*/

void SET_GLOBAL_INT(void)
{
	SET_BIT(SREG, 7);
}

/*
	Function Name        : EXTERNAL_INT0_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize external int 0 with the selected trigger mode
*/

void EXTERNAL_INT0_INIT(void)
{
	SET_GLOBAL_INT();
	SET_BIT(GICR, 6);
	#if		EXTERNAL_INT0_TRIGGER_MODE == LOW_LEVEL_MODE
	CLR_BIT(MCUCR, 0);
	CLR_BIT(MCUCR, 1);
	#elif	EXTERNAL_INT0_TRIGGER_MODE == ANY_LOGICAL_CHANGE
	SET_BIT(MCUCR, 0);
	CLR_BIT(MCUCR, 1);
	#elif	EXTERNAL_INT0_TRIGGER_MODE == FALLING_EDGE_MODE
	CLR_BIT(MCUCR, 0);
	SET_BIT(MCUCR, 1);
	#elif	EXTERNAL_INT0_TRIGGER_MODE == RISING_EDGE_MODE
	SET_BIT(MCUCR, 0);
	SET_BIT(MCUCR, 1);
	#endif
}

/*
	Function Name        : EXTERNAL_INT1_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize external int 1 with the selected trigger mode
*/

void EXTERNAL_INT1_INIT(void)
{
	SET_GLOBAL_INT();
	SET_BIT(GICR, 7);
	#if		EXTERNAL_INT1_TRIGGER_MODE == LOW_LEVEL_MODE
	CLR_BIT(MCUCR, 2);
	CLR_BIT(MCUCR, 3);
	#elif	EXTERNAL_INT1_TRIGGER_MODE == ANY_LOGICAL_CHANGE
	SET_BIT(MCUCR, 2);
	CLR_BIT(MCUCR, 3);
	#elif	EXTERNAL_INT1_TRIGGER_MODE == FALLING_EDGE_MODE
	CLR_BIT(MCUCR, 2);
	SET_BIT(MCUCR, 3);
	#elif	EXTERNAL_INT1_TRIGGER_MODE == RISING_EDGE_MODE
	SET_BIT(MCUCR, 2);
	SET_BIT(MCUCR, 3);
	#endif
}

/*
	Function Name        : EXTERNAL_INT2_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize external int 2 with the selected trigger mode
*/


void EXTERNAL_INT2_INIT(void)
{
	SET_GLOBAL_INT();
	SET_BIT(GICR, 5);
	#if		EXTERNAL_INT2_TRIGGER_MODE == FALLING_EDGE_MODE
	CLR_BIT(MCUCSR, 6);
	#elif	EXTERNAL_INT2_TRIGGER_MODE == RISING_EDGE_MODE
	SET_BIT(MCUCSR, 6);
	#endif
}

void (*CALLBACK_PTR_INT_0) (void) = 0;

/*
	Function Name        : EXTERNAL_INIT0_SET_CALLBACK
	Function Returns     : void
	Function Arguments   : void
	Function Description : pass the address of the function of upper layer to perform in this layer
*/

void EXTERNAL_INIT0_SET_CALLBACK( void (*COPY_FUNCTION) (void))
{
	CALLBACK_PTR_INT_0 = COPY_FUNCTION;
	
}
// int service routine of ext int 0
ISR(INT0_vect)
{
	if(CALLBACK_PTR_INT_0 != 0)
	{
		CALLBACK_PTR_INT_0();
	}
}

void (*CALLBACK_PTR_INT_1) (void) = 0;

/*
	Function Name        : EXTERNAL_INIT1_SET_CALLBACK
	Function Returns     : void
	Function Arguments   : void
	Function Description : pass the address of the function of upper layer to perform in this layer
*/

void EXTERNAL_INIT1_SET_CALLBACK( void (*COPY_FUNCTION) (void))
{
	CALLBACK_PTR_INT_1 = COPY_FUNCTION;
	
}


// int service routine of ext int 1

ISR(INT1_vect)
{
	if(CALLBACK_PTR_INT_1 != 0)
	{
		CALLBACK_PTR_INT_1();
	}
}