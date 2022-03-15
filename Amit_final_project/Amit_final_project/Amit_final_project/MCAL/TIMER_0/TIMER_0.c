/*
 * TIMER_0.c
 *
 * Created: 2/26/2022 8:03:43 PM
 *  Author: alkods
 */ 

#include "TIMER_0.h"

uint32 NUM_OVF = 0;
uint32 Init_value = 0;

/*
	Function Name        : TIMER_0_INIT
	Function Returns     : void
	Function Arguments   : void
	Function Description : Initialize timer_0 with the selected mode 
*/

void TIMER_0_INIT(void)
{
	#if TIMER_0_MODE   ==	NORMAL_MODE
	CLR_BIT(TCCR0, 3);
	CLR_BIT(TCCR0, 6);
	#elif TIMER_0_MODE ==	CTC_MODE
	CLR_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);
	#elif TIMER_0_MODE ==	FAST_PWM
	SET_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);
	SET_BIT(TCCR0, 5);			// SELECT NON-INVERTING MODE
	#endif
	TIMER_0_INT_STATE();
}

/*
	Function Name        : TIMER_0_INT_STATE
	Function Returns     : void
	Function Arguments   : void
	Function Description : activate the inturrpt of the selected mode of the timer 
*/


void TIMER_0_INT_STATE(void)
{
	#if TIMER_0_INT_FLAG	==	ENABLE
		#if TIMER_0_MODE ==  NORMAL_MODE 
			SET_BIT(SREG, 7);
			SET_BIT(TIMSK, 0);
		#elif TIMER_0_MODE == CTC_MODE
			SET_BIT(SREG, 7);
			SET_BIT(TIMSK, 4);
		#endif
	#endif
}

/*
	Function Name        : TIMER_0_START
	Function Returns     : void
	Function Arguments   : void
	Function Description : select the require pre-scaling of the selected timer mode
*/

void TIMER_0_START(void)
{
	#if TIMER_0_MODE   ==	NORMAL_MODE
	SET_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	SET_BIT(TCCR0, 2);
	#elif TIMER_0_MODE ==	CTC_MODE
	SET_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	SET_BIT(TCCR0, 2);
	#elif TIMER_0_MODE ==	FAST_PWM
	CLR_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	SET_BIT(TCCR0, 2);
	#endif
}

/*
	Function Name        : TIMER_0_Stop
	Function Returns     : void
	Function Arguments   : void
	Function Description : select no pre-scaling
*/

void TIMER_0_STOP(void)
{
	CLR_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	CLR_BIT(TCCR0, 2);
}

/*
	Function Name        : TIMER_0_SET_DELAY
	Function Returns     : void
	Function Arguments   : uint32 delay_ms 
	Function Description : set the delay of timers using the suitable equations for normal & ctc
*/

void TIMER_0_SET_DELAY(uint32 Delay_ms)
{
	#if TIMER_0_MODE  ==   NORMAL_MODE
	uint8 Tick_Time = (1024/16) ;
	uint32 Tot_Ticks = (Delay_ms * 1000) / Tick_Time ;
	NUM_OVF = Tot_Ticks / 256 ;
	Init_value = 256 - (Tot_Ticks % 256) ;
	TCNT0 = Init_value ;
	NUM_OVF++;	
	#elif TIMER_0_MODE  ==  CTC_MODE
	// FNDING TICK_TIME
	uint8 TICK_TIME = ( 1024 / 16 );
	// FINDINH TOTAL_TICKS
	uint32 TOTAL_TICKS = ( Delay_ms * 1000 ) / TICK_TIME;
	OCR0 = TOTAL_TICKS - 1;
	NUM_OVF ++ ;
	#endif
}

/*
	Function Name        : TIMER_0_PWM_SET_DUTY_CYCLE
	Function Returns     : void
	Function Arguments   : uint8 duty_cycle
	Function Description : set duty_cycle value of pwm mode
*/

void TIMER_0_PWM_SET_DUTY_CYCLE(uint8 Duty_cycle)
{
	#if TIMER_0_MODE  ==  FAST_PWM
	OCR0 = ((Duty_cycle * 256) / 100) - 1 ;
	#endif
}

void (*CALLBACK_PTTR_TIMER_0) (void) = 0;

/*
	Function Name        : TIMER_2_INIT_SET_CALLBACK
	Function Returns     : void
	Function Arguments   : void
	Function Description : pass the address of the function of upper layer to perform in this layer
*/

void TIMER_0_INIT_SET_CALLBACK( void (*COPY_FUNCTION) (void))
{
	CALLBACK_PTTR_TIMER_0 = COPY_FUNCTION;
}


// inturrpt service routine of timer0 ovf
ISR(TIMER0_OVF_vect)
{
	if(CALLBACK_PTTR_TIMER_0 != 0)
	{
		CALLBACK_PTTR_TIMER_0();
	}
}