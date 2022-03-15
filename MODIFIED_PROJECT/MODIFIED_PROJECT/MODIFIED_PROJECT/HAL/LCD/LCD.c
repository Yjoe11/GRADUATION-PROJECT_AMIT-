/*
 * LCD.c
 *
 *  Created on: Oct 26, 2021
 *      Author: ALKODS
 */

#include "LCD.h"
#include "MATHMATICS.h"

void LCD_Init(void)
{
#if LCD_MODE  ==  8 //init the pins dir in 8bit mode

	DIO_SetPinDir(LCD_8BIT_CMD_PORT,LCD_RS_PIN, DIO_PIN_OUTPUT );
	DIO_SetPinDir(LCD_8BIT_CMD_PORT,LCD_RW_PIN, DIO_PIN_OUTPUT );
	DIO_SetPinDir(LCD_8BIT_CMD_PORT,LCD_E_PIN, DIO_PIN_OUTPUT );
	DIO_SetPortDir(LCD_8BIT_DATA_PORT,DIO_PORT_OUTPUT);

	_delay_ms(100);
// send commands to lcd for init as 8 bit mode
	LCD_WriteCommand(0x38);  // sad3et kadh fun write 0x38
	LCD_WriteCommand(0x0c);     //kadh close cursor
	LCD_WriteCommand(0x01);    //kadh clear lcd
	LCD_WriteCommand(0x06);   // kadh cursor right or inc
	LCD_WriteCommand(0x02);  // kadh 3malth return to home
#elif LCD_MODE == 4 //init the pins dir in 4bit mode

	DIO_SetPinDir(LCD_4BIT_CMD_PORT,LCD_RS_PIN, DIO_PIN_OUTPUT );
	DIO_SetPinDir(LCD_4BIT_CMD_PORT,LCD_RW_PIN, DIO_PIN_OUTPUT );
	DIO_SetPinDir(LCD_4BIT_CMD_PORT,LCD_E_PIN, DIO_PIN_OUTPUT );

	DIO_SetPinDir(LCD_4BIT_DATA_PORT, D4_PIN, DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_DATA_PORT, D5_PIN, DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_DATA_PORT, D6_PIN, DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_DATA_PORT, D7_PIN, DIO_PIN_OUTPUT);

	_delay_ms(100);
	// send commands to lcd for init as 4 bit mode
	LCD_WriteCommand(0x33);
	LCD_WriteCommand(0x32);
	LCD_WriteCommand(0x28);

	LCD_WriteCommand(0x0c);     //kadh close cursor
	LCD_WriteCommand(0x01);    //kadh clear lcd
	LCD_WriteCommand(0x06);   // kadh cursor right or inc
	LCD_WriteCommand(0x02);  // kadh 3malth return to home
#endif
}

void LCD_WriteCommand(uint8 cmd)  // rs cmd reg walh data reg
{
 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_RS_PIN,DIO_PIN_LOW );
 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_RW_PIN,DIO_PIN_LOW );
 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_LOW );

 PORTA = (cmd & 0xf0)|(PORTA & 0x0f);

 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_HIGH);
 _delay_ms(1); // bta3 latch
 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_LOW );

 PORTA = (cmd << 4)|(PORTA & 0x0f);

 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_HIGH);
  _delay_ms(1); // bta3 latch
  DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_LOW );

  _delay_ms(5);
}
void LCD_WriteChar(uint8 chr)
{
	 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_RS_PIN,DIO_PIN_HIGH ); // Rs High bass kadh htktb 3lah data reg
	 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_RW_PIN,DIO_PIN_LOW );
	 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_LOW );

	 PORTA = (chr & 0xf0)|(PORTA & 0x0f);

	 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	 _delay_ms(1); // bta3 latch
	 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_LOW );

	 PORTA = (chr << 4)|(PORTA & 0x0f);

	 DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	  _delay_ms(1); // bta3 latch
	  DIO_SetPinVal(LCD_4BIT_CMD_PORT,LCD_E_PIN,DIO_PIN_LOW );

	  _delay_ms(5);
}

void LCD_WriteString(uint8* str)
{
uint8 i=0;
while(str[i] != '\0')
{
	LCD_WriteChar(str[i]);
	i++;
}
}
void LCD_GoTo(uint8 row , uint8  col) // 3az akteb feh ay mkan ana 3ayzh
{
uint8 pos[2]={0x80,0xc0};
LCD_WriteCommand(pos[row]+col);
}
void LCD_Clear(void)
{
LCD_WriteCommand(0x01);
}

void LCD_WriteInteger(sint32 num,uint8 kam_5ana)
{
	uint32 VALUE;
	if (num>=0)
	{
		for (uint8 i=kam_5ana;i>0;i--)
		{
			uint8 ASCII= 48;
			VALUE=(num % Pow_int(10,(i)) - num % Pow_int(10,(i-1))) / Pow_int(10,(i-1));
			for (uint8 j=0;j<=9;j++)
			{
				if (j==VALUE)
				{
					LCD_WriteChar(ASCII);
				}
				ASCII++;
			}
		}
	}
	else
	{
		LCD_WriteChar('-');
		num=num*(-1);
		for (uint8 i=kam_5ana;i>0;i--)
		{
			uint8 ASCII= 48;
			VALUE=(num % Pow_int(10,(i)) - num % Pow_int(10,(i-1))) / Pow_int(10,(i-1));
			for (uint8 j=0;j<=9;j++)
			{
				if (j==VALUE)
				{
					LCD_WriteChar(ASCII);
				}
				ASCII++;
			}
		}
	}
	
}