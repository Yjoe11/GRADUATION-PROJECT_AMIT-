/*
 * TIMER_2.h
 *
 * Created: 3/2/2022 5:32:51 PM
 *  Author: alkods
 */ 


#ifndef TIMER_2_H_
#define TIMER_2_H_

#include <avr/interrupt.h>
#include "../../LIB/Atmega32_Register.h"
#include "../../LIB/BIT_Math.h"
#include "TIMER_2_CONFIGURATION.h"




void TIMER_2_SELECT_MODE(uint8 MODE, uint8 INT_ACTIVATE);

void TIMER_2_INIT(void);

void TIMER_2_INT_STATE(void);

void TIMER_2_START(void);

void TIMER_2_STOP(void);

void TIMER_2_SET_DELAY(uint32 Delay_ms);

void TIMER_2_PWM_SET_DUTY_CYCLE(uint8 Duty_cycle);

void TIMER_2_INIT_SET_CALLBACK( void (*COPY_FUNCTION) (void));


#endif /* TIMER_2_H_ */