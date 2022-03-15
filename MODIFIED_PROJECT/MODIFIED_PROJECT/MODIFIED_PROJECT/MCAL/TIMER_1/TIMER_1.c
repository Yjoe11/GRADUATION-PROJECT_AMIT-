/*
 * TIMER_1.c
 *
 * Created: 3/10/2022 6:36:58 PM
 *  Author: alkods
 */ 


#include "TIMER_1.h"

uint8 MODE_1 = FAST_PWM_S;
uint8 INT_TIMER_1 = DISABLE;

void TIMER_1_SELECT_MODE(uint8 MODE, uint8 INT_ACTIVATE)
{
	MODE_1 = MODE;
	INT_TIMER_1 = INT_ACTIVATE;
}

void TIMER_1_INIT(void)
{
	switch(MODE_1)
	{
		case NORMAL_MODE:
		CLR_BIT (TCCR1A, 0);
		CLR_BIT (TCCR1A, 1);
		CLR_BIT (TCCR1B, 3);
		CLR_BIT (TCCR1B, 4);
		break;
		
		case FAST_PWM_S:
		CLR_BIT (TCCR1A, 0);
		SET_BIT (TCCR1A, 1);
		SET_BIT (TCCR1B, 3);
		SET_BIT (TCCR1B, 4);
		
		SET_BIT (TCCR1A , 7);		// SELECTING NON_INVERTING_MODE
		
		ICR1 = 1250 ;				// TOP VALUE WE NEED IN THIS SERVO
		break;
		
		default:
		break;
	}
	TIMER_1_INIT_STATE();
}

void TIMER_1_INIT_STATE(void)
{
	if (INT_TIMER_1)
		{
			if(MODE_1==NORMAL_MODE)
			{
			SET_BIT(SREG, 7);
			SET_BIT(TIMSK, 4);
			}
		}
}

void TIMER_1_START(void)
{
	switch(MODE_1)
	{
		case NORMAL_MODE:
		SET_BIT(TCCR1B , 0);
		CLR_BIT(TCCR1B , 1);
		SET_BIT(TCCR1B , 2);
		break;
		
		case FAST_PWM_S:
		CLR_BIT(TCCR1B , 0);
		CLR_BIT(TCCR1B , 1);
		SET_BIT(TCCR1B , 2);
		break;
		
		default:
		break;
	}
}

void TIMER_1_STOP(void)
{
	CLR_BIT ( TCCR1B,0);
	CLR_BIT ( TCCR1B,1);
	CLR_BIT ( TCCR1B,2);
}

//void TIMER_1_SET_DELAY(uint32 Delay_ms);

void TIMER_1_SET_DUTY_CYCLE(uint8 Duty_Cycle)
{
	OCR1A = ((Duty_Cycle * 1250 ) /100 ) -1 ;
}