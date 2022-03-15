/*
 * TIMER_2.c
 *
 * Created: 3/2/2022 5:33:07 PM
 *  Author: alkods
 */ 


#include "TIMER_2.h"

uint32 NUM_OVF_2 = 0;
uint32 Init_value_2 = 0;

TIMER_2_MODE MODE_2 = NORMAL_MODE;
INT_FLAG_2 INT_TIMER_2 = ENABLE;


void TIMER_2_SELECT_MODE(uint8 MODE, uint8 INT_ACTIVATE)
{
	MODE_2 = MODE;
	INT_TIMER_2 = INT_ACTIVATE;
}

void TIMER_2_INIT(void)
{
	switch(MODE_2)
	{
		case NORMAL_MODE:
		CLR_BIT(TCCR2, 3);
		CLR_BIT(TCCR2, 6);
		break;
		
		case CTC_MODE:
		SET_BIT(TCCR2, 3);
		CLR_BIT(TCCR2, 6);
		break;
		
		case FAST_PWM:
		SET_BIT(TCCR2, 3);
		SET_BIT(TCCR2, 6);
		
		SET_BIT(TCCR2, 5);			// SELECT NON-INVERTING MODE
		break;
		
		default:
		break;
	}
	
	TIMER_2_INT_STATE();
}

void TIMER_2_INT_STATE(void)
{
	if(INT_TIMER_2)
	{
		switch(MODE_2)
		{
			case NORMAL_MODE:
			SET_BIT(SREG, 7);
			SET_BIT(TIMSK, 6);
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

void TIMER_2_START(void)
{
	switch (MODE_2)
	{
		case NORMAL_MODE:
		SET_BIT(TCCR2, 0);
		SET_BIT(TCCR2, 1);
		SET_BIT(TCCR2, 2);
		break;
		
		case CTC_MODE:
		SET_BIT(TCCR2, 0);
		CLR_BIT(TCCR2, 1);
		SET_BIT(TCCR2, 2);
		break;
		
		case FAST_PWM:
		CLR_BIT(TCCR2, 0);
		CLR_BIT(TCCR2, 1);
		SET_BIT(TCCR2, 2);
		break;
		
		default:
		break;
	}
}

void TIMER_2_STOP(void)
{
	CLR_BIT(TCCR2, 0);
	CLR_BIT(TCCR2, 1);
	CLR_BIT(TCCR2, 2);
}



void TIMER_2_SET_DELAY(uint32 Delay_ms)
{
	if (MODE_2 == NORMAL_MODE)
	{
		uint8 Tick_Time = (1024/16) ;
		uint32 Tot_Ticks = (Delay_ms * 1000) / Tick_Time ;
		NUM_OVF_2 = Tot_Ticks / 256 ;
		Init_value_2 = 256 - (Tot_Ticks % 256) ;
		TCNT2 = Init_value_2 ;
		NUM_OVF_2++;
	}
	else if (MODE_2 == CTC_MODE)
	{
		//case (CTC_MODE):
		// FNDING TICK_TIME
		uint8 TICK_TIME = ( 1024 / 16 );
		// FINDINH TOTAL_TICKS
		uint32 TOTAL_TICKS = ( Delay_ms * 1000 ) / TICK_TIME;
		OCR2 = TOTAL_TICKS - 1;
		NUM_OVF_2++ ;

	}
}

void TIMER_2_PWM_SET_DUTY_CYCLE(uint8 Duty_cycle)
{
	if (MODE_2 == FAST_PWM)
	OCR2 = ((Duty_cycle * 256) / 100) - 1 ;
}


void (*CALLBACK_PTTR) (void) = 0;

void TIMER_2_INIT_SET_CALLBACK( void (*COPY_FUNCTION) (void))
{
	CALLBACK_PTTR = COPY_FUNCTION;
}

ISR(TIMER2_OVF_vect)
{
	if(CALLBACK_PTTR != 0)
	{
		CALLBACK_PTTR();
	}
}