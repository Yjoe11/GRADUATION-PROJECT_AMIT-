/*
 * ULTRASONIC.h
 *
 * Created: 3/9/2022 4:59:37 PM
 *  Author: alkods
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../../LIB/Atmega32_Register.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIMER_2/TIMER_2.h"
#include "../../MCAL/EXTERNAL_INT/EXTERNAL_INT.h"
#include "ULTRASONIC_CONFIGURATION.h"
//#include "../LCD/LCD.h"
#include <avr/interrupt.h>
#define F_CPU  16000000
#include <util/delay.h>


void ULTRASONIC_INIT(void);
void ULTRASONIC_TREGGIER(void);
void ULTRASONIC_EXT_INT(void);
void ULTRASONIC_OVF_INT(void);
void ULTRASONIC_ACTION_SET_CALLBACK( void (*COPY_FUNCTION) (uint32 DISTANCE));

#endif /* ULTRASONIC_H_ */