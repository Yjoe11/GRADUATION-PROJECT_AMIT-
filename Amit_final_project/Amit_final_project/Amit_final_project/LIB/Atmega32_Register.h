/*
 * Atmega32_Register.h
 *
 *  Created on: Oct 22, 2021
 *      Author: ALKODS
 */

#ifndef ATMEGA32_REGISTER_H_
#define ATMEGA32_REGISTER_H_
#include "STD.h"

#define PORTA			*((uint8*)0x3B)
#define DDRA			*((uint8*)0x3A)
#define PINA			*((volatile uint8*)0x39)

#define PORTB			*((uint8*)0x38)
#define DDRB			*((uint8*)0x37)
#define PINB			*((volatile uint8*)0x36)

#define PORTC			*((uint8*)0x35)
#define DDRC			*((uint8*)0x34)
#define PINC			*((volatile uint8*)0x33)

#define PORTD			*((uint8*)0x32)
#define DDRD			*((uint8*)0x31)
#define PIND			*((volatile uint8*)0x30)


/***************************** PREPHERAL REGISTER *******************************/

#define SREG			*((volatile uint8*)0x5F)								
// STATUS REGISTER & WE USE BIT NO.7 FOR INDICATION OF GLOBAL INTERRUPT 

#define GICR			*((volatile uint8*)0x5B)								
// GENERAL INTERRUPT CONTROL REGISTER & WE USE BIT NO. 7,6,5 TO MAKE EXTERNAL INTERRUPT ENABLED INT0, INT1, INT2

#define	GIFR			*((volatile uint8*)0x5A)
// GENERAL INTERRUPT FLAG REGISTER & WE USE THIS REGISTER TO INDICATE THE FLAG OF INT0-->2

#define MCUCR			*((volatile uint8*)0x55)
// MCU CONTROL REGISTER & WE USE IT TO SENCE CONTROL OF TRIGER FOR INT0-->1

#define MCUCSR			*((volatile uint8*)0x54)
// MCU CONTROL AND STATUS REGISTER, WE USE BIT NO.6 THE SENCE CONTROL OF INT2


/**********************************************   ADC REGISTER   ******************************************/

/* 
ADC MUL selection register 
bits 7:6 used for select supplyment refrance
bit 5 used for select left adjust result by set one otherwise for right adjust
bits 4:0 used for selects which combination of analog inputs are connected to the ADC.
*/
#define ADMUX				(*(volatile uint8*)(0x27))

/*
ADC control & status register 
bit 7 used for accessing ADC ENABLE
bit 6 used for start conversion
bit 5 used for auto trigger enable 
bit 4 indicate the end of conversion and ADC interrupt flag
bit 3 used for ADC interrupt enable
bits 2:0 used for determine the division factor between the XTAL frequency and the input clock to the ADC.
*/
#define	ADCSRA				(*(volatile uint8*)(0x26))

/*
ADC data registers 
*/
#define ADCH				(*(volatile uint8*)(0x25))
#define ADCL				(*(volatile uint8*)(0x24))
#define ADC_ADJUST			(*(volatile uint16*)(0x24))						// THIS FOR RIGHT ADJUST AND TAKE TWO BYTES DIRECTLY

/*
Special function IO register 
bits 7:5 used for ADC Auto Trigger Source
*/
#define SFIOR				(*(volatile uint8*)(0x50))



/************************************************************************/
/*						TIMER_0  REGISTER                               */
/************************************************************************/


// TIMER or COUNTER register
#define TCNT0				(*(volatile uint8 *)(0x52))

/*   TIMER or COUNTER control rigister
 *   bit 7 used for activate force output compare and this bit is always zero
 *	 bit 6 and bit 3 these bits used for control the counting sequance to activate modes see table.38 page.78
 *	 bit 4 and bit 5 these bits are used for compare match output mode
 *	 bits 2:0 are used for select clock source "prescaling" see table.42 page.79
 */
#define TCCR0				(*(volatile uint8 *)(0x53))

// output compare register
#define OCR0				(*(volatile uint8 *)(0x5C))

/*	 timer control interrupt mask 
 *   bit 1 used for enable output compare match interrupt
 *   bit 0 used for enable overflow interrupt
 */
#define TIMSK				(*(volatile uint8 *)(0x59))


/************************************************************************/
/*						TIMER_1  REGISTER                               */
/************************************************************************/

/*																														
 *		TIMER/COUNTER control register A
 *		Bit 7:6 compare output mode for channel A
 *		Bit 5:4 compare output mode for channel B
 *		Bit 3:2 force output compare for channels A&B / 3 for A and 2 for B
 *		BITS 1:0 on tccr1a plus BITS 3:4 on tccrb is for chosing the waveform genration mode form table.47 page.107 
 *  
 *		TIMER/COUNTER control register B
 *		Bit 7 input capture noise canceler
 *		Bit 6 input capture edge select 
 *		Bit 5 reversed bit 
 *		Bits 2:0 clk select "prescaling"
 */
#define	TCCR1A				(*(volatile uint8 *)(0x4F))
#define TCCR1B				(*(volatile uint8 *)(0x4E))

/* TIMER COUNTER REGISTER */
#define TCNT1_AD			(*(volatile uint16 *)(0x4C))

/* OUTPUT COMPARE REGISTERS */
#define OCR1A				(*(volatile uint16 *)(0x4A))
#define ORC1B				(*(volatile uint16 *)(0x48))

/* INPUT CAPTURE REGISTER */
#define ICR1				(*(volatile uint16 *)(0x46))




#endif /* ATMEGA32_REGISTER_H_ */
