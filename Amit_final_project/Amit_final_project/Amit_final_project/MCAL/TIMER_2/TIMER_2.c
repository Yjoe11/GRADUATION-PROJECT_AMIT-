/*
 * TIMER_2.c
 *
 * Created: 3/2/2022 5:33:07 PM
 *  Author: alkods
 */ 


#include "TIMER_2.h"

uint32 NUM_OVF_2 = 0;
uint32 Init_value_2 = 0;

/*
	Function Name        : TIMER_2_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize timer_2 with the selected mode 
*/

void TIMER_2_INIT(void)
{
	#if TIMER_2_MODE   ==	NORMAL_MODE
	
	CLR_BIT(TCCR2, 3);
	CLR_BIT(TCCR2, 6);
	
	#elif TIMER_2_MODE ==	CTC_MODE
	
	SET_BIT(TCCR2, 3);
	CLR_BIT(TCCR2, 6);
	
	#elif TIMER_2_MODE ==	FAST_PWM
	SET_BIT(TCCR2, 3);
	SET_BIT(TCCR2, 6);
	
	SET_BIT(TCCR2, 5);			// SELECT NON-INVERTING MODE
	
	#endif
	TIMER_2_INT_STATE();
}

/*
	Function Name        : TIMER_2_INT_STATE
	Function Returns     : void
	Function Arguments   : void
	Function Description : activate the inturrpt of the selected mode of the timer 
*/

void TIMER_2_INT_STATE(void)
{
	#if TIMER_2_INT_FLAG	==	ENABLE
	#if TIMER_2_MODE ==  NORMAL_MODE
	
	SET_BIT(SREG, 7);
	SET_BIT(TIMSK, 6);
	
	#elif TIMER_2_MODE == CTC_MODE
	SET_BIT(SREG, 7);
	SET_BIT(TIMSK, 4);
	#endif
	#endif
}

/*
	Function Name        : TIMER_2_START
	Function Returns     : void
	Function Arguments   : void
	Function Description : select the require pre-scaling of the selected timer mode
*/

void TIMER_2_START(void)
{
	#if TIMER_2_MODE   ==	NORMAL_MODE
	SET_BIT(TCCR2, 0);
	SET_BIT(TCCR2, 1);
	SET_BIT(TCCR2, 2);
	#elif TIMER_2_MODE ==	CTC_MODE
	SET_BIT(TCCR2, 0);
	CLR_BIT(TCCR2, 1);
	SET_BIT(TCCR2, 2);
	#elif TIMER_2_MODE ==	FAST_PWM
	CLR_BIT(TCCR2, 0);
	CLR_BIT(TCCR2, 1);
	SET_BIT(TCCR2, 2);
	#endif
}

/*
	Function Name        : TIMER_2_Stop
	Function Returns     : void
	Function Arguments   : void
	Function Description : select no pre-scaling
*/


void TIMER_2_STOP(void)
{
	CLR_BIT(TCCR2, 0);
	CLR_BIT(TCCR2, 1);
	CLR_BIT(TCCR2, 2);
}

/*
	Function Name        : TIMER_2_SET_DELAY
	Function Returns     : void
	Function Arguments   : uint32 delay_ms 
	Function Description : set the delay of timers using the suitable equations for normal & ctc
*/


void TIMER_2_SET_DELAY(uint32 Delay_ms)
{
	#if TIMER_2_MODE  ==   NORMAL_MODE
	uint8 Tick_Time = (1024/16) ;
	uint32 Tot_Ticks = (Delay_ms * 1000) / Tick_Time ;
	NUM_OVF_2 = Tot_Ticks / 256 ;
	Init_value_2 = 256 - (Tot_Ticks % 256) ;
	TCNT2 = Init_value_2 ;
	NUM_OVF_2++;
	
	#elif TIMER_2_MODE  ==  CTC_MODE
	// FNDING TICK_TIME
	uint8 TICK_TIME = ( 1024 / 16 );
	// FINDINH TOTAL_TICKS
	uint32 TOTAL_TICKS = ( Delay_ms * 1000 ) / TICK_TIME;
	OCR2 = TOTAL_TICKS - 1;
	NUM_OVF_2++ ;
	#endif
}

/*
	Function Name        : TIMER_2_PWM_SET_DUTY_CYCLE
	Function Returns     : void
	Function Arguments   : uint8 duty_cycle
	Function Description : set duty_cycle value of pwm mode
*/

void TIMER_2_PWM_SET_DUTY_CYCLE(uint8 Duty_cycle)
{
	#if TIMER_2_MODE  ==  FAST_PWM
	OCR2 = ((Duty_cycle * 256) / 100) - 1 ;
	#endif
}


void (*CALLBACK_PTTR) (void) = 0; 

/*
	Function Name        : TIMER_2_INIT_SET_CALLBACK
	Function Returns     : void
	Function Arguments   : void
	Function Description : pass the address of the function of upper layer to perform in this layer
*/


void TIMER_2_INIT_SET_CALLBACK( void (*COPY_FUNCTION) (void))
{
	CALLBACK_PTTR = COPY_FUNCTION;
}


// inturrpt service routine of timer2 ovf
ISR(TIMER2_OVF_vect)
{
	if(CALLBACK_PTTR != 0)
	{
		CALLBACK_PTTR();
	}
}