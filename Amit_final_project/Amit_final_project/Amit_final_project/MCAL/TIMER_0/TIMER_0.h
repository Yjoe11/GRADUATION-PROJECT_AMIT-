/*
 * TIMER_0.h
 *
 * Created: 2/26/2022 8:03:26 PM
 *  Author: alkods
 */ 


#ifndef TIMER_0_H_
#define TIMER_0_H_

#include "../../LIB/Atmega32_Register.h"
#include "../../LIB/BIT_Math.h"
#include "TIMER0_CONFIGURATION.h"
#include <avr/interrupt.h>

#define NORMAL_MODE			1
#define PWM_PHASE_CORRECT	2
#define CTC_MODE			3
#define FAST_PWM			4

#define ENABLE				1
#define DISABLE				0

void TIMER_0_INIT(void);
void TIMER_0_INT_STATE(void);
void TIMER_0_START(void);
void TIMER_0_STOP(void);
void TIMER_0_SET_DELAY(uint32 Delay_ms);
void TIMER_0_PWM_SET_DUTY_CYCLE(uint8 Duty_cycle);
void TIMER_0_INIT_SET_CALLBACK( void (*COPY_FUNCTION) (void));




#endif /* TIMER_0_H_ */