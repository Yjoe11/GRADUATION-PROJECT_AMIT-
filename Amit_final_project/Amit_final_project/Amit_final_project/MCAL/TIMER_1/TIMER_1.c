/*
 * TIMER_1.c
 *
 * Created: 3/10/2022 6:36:58 PM
 *  Author: alkods
 */ 


#include "TIMER_1.h"

/*
	Function Name        : TIMER_1_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize timer_1 with the selected mode 
*/

void TIMER_1_INIT(void)
{
	#if TIMER_1_MODE == NORMAL_MODE
		CLR_BIT (TCCR1A, 0);
		CLR_BIT (TCCR1A, 1);
		CLR_BIT (TCCR1B, 3);
		CLR_BIT (TCCR1B, 4);
	#elif TIMER_1_MODE == FAST_PWM_S
		CLR_BIT (TCCR1A, 0);
		SET_BIT (TCCR1A, 1);
		SET_BIT (TCCR1B, 3);
		SET_BIT (TCCR1B, 4);
		
		SET_BIT (TCCR1A , 7);		// SELECTING NON_INVERTING_MODE
		
		ICR1 = 1250 ;				// TOP VALUE WE NEED IN THIS SERVO 
	#endif
	TIMER_1_INIT_STATE();
}

/*
	Function Name        : TIMER_1_INT_STATE
	Function Returns     : void
	Function Arguments   : void
	Function Description : activate the inturrpt of the selected mode of the timer 
*/

void TIMER_1_INIT_STATE(void)
{
	#if TIMER_1_INT_FLAG == ENABLE
		#if TIMER_1_MODE == NORMAL_MODE
		SET_BIT(SREG, 7);
		SET_BIT(TIMSK, 4);
		#endif
	#endif
}

/*
	Function Name        : TIMER_1_START
	Function Returns     : void
	Function Arguments   : void
	Function Description : select the require pre-scaling of the selected timer mode
*/

void TIMER_1_START(void)
{
	#if TIMER_1_MODE   ==	NORMAL_MODE
	SET_BIT(TCCR1B , 0);
	CLR_BIT(TCCR1B , 1);
	SET_BIT(TCCR1B , 2);
	#elif TIMER_1_MODE ==	FAST_PWM_S
	CLR_BIT(TCCR1B , 0);
	CLR_BIT(TCCR1B , 1);
	SET_BIT(TCCR1B , 2);
	#endif
}

/*
	Function Name        : TIMER_1_Stop
	Function Returns     : void
	Function Arguments   : void
	Function Description : select no pre-scaling
*/

void TIMER_1_STOP(void)
{
	CLR_BIT ( TCCR1B,0);
	CLR_BIT ( TCCR1B,1);
	CLR_BIT ( TCCR1B,2);
}

//void TIMER_1_SET_DELAY(uint32 Delay_ms);



/*
	Function Name        : TIMER_1_PWM_SET_DUTY_CYCLE
	Function Returns     : void
	Function Arguments   : uint8 duty_cycle
	Function Description : set duty_cycle value of pwm mode
*/


void TIMER_1_SET_DUTY_CYCLE(uint8 Duty_Cycle)
{
	OCR1A = ((Duty_Cycle * 1250 ) /100 ) -1 ;
}