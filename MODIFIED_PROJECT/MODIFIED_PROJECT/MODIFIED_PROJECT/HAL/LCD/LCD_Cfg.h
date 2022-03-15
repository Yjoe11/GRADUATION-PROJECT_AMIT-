/*
 * LCD_Cfg.h
 *
 *  Created on: Oct 26, 2021
 *      Author: ALKODS
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_



#define LCD_MODE	4        // leee 8 bit walh 4 bit

#define LCD_8BIT_CMD_PORT    	DIO_PORTD  // kadh kadh m4 h4t5l 8bit
#define LCD_8BIT_DATA_PORT		DIO_PORTC

#define LCD_4BIT_CMD_PORT    	DIO_PORTB
#define LCD_4BIT_DATA_PORT		DIO_PORTA

#define LCD_RS_PIN				DIO_PIN1
#define LCD_RW_PIN				DIO_PIN2
#define LCD_E_PIN				DIO_PIN3

#define D0_PIN					DIO_PIN0
#define D1_PIN					DIO_PIN1
#define D2_PIN					DIO_PIN2
#define D3_PIN					DIO_PIN3
#define D4_PIN					DIO_PIN4
#define D5_PIN					DIO_PIN5
#define D6_PIN					DIO_PIN6
#define D7_PIN					DIO_PIN7




#endif /* LCD_CFG_H_ */
