/*
 * TIMER_1.h
 *
 * Created: 3/10/2022 6:37:34 PM
 *  Author: alkods
 */ 


#ifndef TIMER_1_H_
#define TIMER_1_H_

#include "../../LIB/Atmega32_Register.h"
#include "../../LIB/BIT_Math.h"
#include "TIMER_1_CONFIGURATION.h"

void TIMER_1_SELECT_MODE(uint8 MODE, uint8 INT_ACTIVATE);

void TIMER_1_INIT(void);

void TIMER_1_INIT_STATE(void);

void TIMER_1_START(void);

void TIMER_1_STOP(void);

//void TIMER_1_SET_DELAY(uint32 Delay_ms);

void TIMER_1_SET_DUTY_CYCLE(uint8 Duty_Cycle);




#endif /* TIMER_1_H_ */