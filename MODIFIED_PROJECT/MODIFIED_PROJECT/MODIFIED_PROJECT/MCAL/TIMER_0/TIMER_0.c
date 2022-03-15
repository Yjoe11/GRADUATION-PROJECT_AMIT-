/*
 * TIMER_0.c
 *
 * Created: 2/26/2022 8:03:43 PM
 *  Author: alkods
 */ 

#include "TIMER_0.h"

uint32 NUM_OVF = 0;
uint32 Init_value = 0;

uint8 MODE_0 = NORMAL_MODE;
uint8 INT_TIMER_0 = ENABLE;

void TIMER_0_SELECT_MODE(uint8 MODE, uint8 INT_ACTIVATE)
{
	MODE_0 = MODE;
	INT_TIMER_0 = INT_ACTIVATE;
}

void TIMER_0_INIT(void)
{
	switch(MODE_0)
	{
		case NORMAL_MODE:
		CLR_BIT(TCCR0, 3);
		CLR_BIT(TCCR0, 6);
		break;
		
		case CTC_MODE:
		CLR_BIT(TCCR0, 3);
		SET_BIT(TCCR0, 6);
		break;
		
		case FAST_PWM:
		SET_BIT(TCCR0, 3);
		SET_BIT(TCCR0, 6);
		
		SET_BIT(TCCR0, 5);			// SELECT NON-INVERTING MODE
		break;
		
		default:
		break;
	}
	TIMER_0_INT_STATE();
}

void TIMER_0_INT_STATE(void)
{
	if(INT_TIMER_0)
	{
		switch(MODE_0)
		{
			case NORMAL_MODE:
			SET_BIT(SREG, 7);
			SET_BIT(TIMSK, 0);
			break;
			
			case CTC_MODE:
			SET_BIT(SREG, 7);
			SET_BIT(TIMSK, 4);
			break;
			
			default:
			break;
			
		}
	}
}

void TIMER_0_START(void)
{
	switch (MODE_0)
	{
		case NORMAL_MODE:
		SET_BIT(TCCR0, 0);
		CLR_BIT(TCCR0, 1);
		SET_BIT(TCCR0, 2);
		break;
		
		case CTC_MODE:
		SET_BIT(TCCR0, 0);
		CLR_BIT(TCCR0, 1);
		SET_BIT(TCCR0, 2);
		break;
		
		case FAST_PWM:
		CLR_BIT(TCCR0, 0);
		CLR_BIT(TCCR0, 1);
		SET_BIT(TCCR0, 2);
		break;
		
		default:
		break;
	}

}

void TIMER_0_STOP(void)
{
	CLR_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	CLR_BIT(TCCR0, 2);
}



void TIMER_0_SET_DELAY(uint32 Delay_ms)
{
	if (MODE_0  ==   NORMAL_MODE)
	{
	uint8 Tick_Time = (1024/16) ;
	uint32 Tot_Ticks = (Delay_ms * 1000) / Tick_Time ;
	NUM_OVF = Tot_Ticks / 256 ;
	Init_value = 256 - (Tot_Ticks % 256) ;
	TCNT0 = Init_value ;
	NUM_OVF++;
	}
	
	else if (MODE_0  ==  CTC_MODE)
	{
	// FNDING TICK_TIME
	uint8 TICK_TIME = ( 1024 / 16 );
	// FINDINH TOTAL_TICKS
	uint32 TOTAL_TICKS = ( Delay_ms * 1000 ) / TICK_TIME;
	OCR0 = TOTAL_TICKS - 1;
	NUM_OVF ++ ;
	}
}


void TIMER_0_PWM_SET_DUTY_CYCLE(uint8 Duty_cycle)
{

	OCR0 = ((Duty_cycle * 256) / 100) - 1 ;

}

void (*CALLBACK_PTTR_TIMER_0) (void) = 0;

void TIMER_0_INIT_SET_CALLBACK( void (*COPY_FUNCTION) (void))
{
	CALLBACK_PTTR_TIMER_0 = COPY_FUNCTION;
}

ISR(TIMER0_OVF_vect)
{
	if(CALLBACK_PTTR_TIMER_0 != 0)
	{
		CALLBACK_PTTR_TIMER_0();
	}
}