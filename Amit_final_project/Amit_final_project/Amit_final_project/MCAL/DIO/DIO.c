/*
 * DIO.c

 *
 *  Created on: Oct 22, 2021
 *      Author: ALKODS
 */
#include "DIO.h"


/*
	Function Name        : DIO_SetPortDir
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8 Dir
	Function Description :  set the direction of port
*/

void DIO_SetPortDir(uint8 Port , uint8 Dir)
{
	switch (Port)
	{
	case DIO_PORTA :
		DDRA = Dir ;
		break;
	case DIO_PORTB :
		DDRB = Dir ;
		break;
	case DIO_PORTC :
		DDRC = Dir ;
		break;
	case DIO_PORTD :
		DDRD = Dir ;
		break;
	default :
		break;
	}

}

/*
	Function Name        : DIO_SetPinDir
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8 Pin    ,uint8 Dir 
	Function Description : set the direction of pins
*/
void DIO_SetPinDir( uint8 Port , uint8 Pin    ,uint8 Dir    )
{
	switch (Dir)
	{
	case DIO_PIN_OUTPUT:
		switch(Port)

		{
		case DIO_PORTA:
	SET_BIT(DDRA,Pin);
		break;

		case DIO_PORTB:
		SET_BIT(DDRB,Pin);
			break;

		case DIO_PORTC:
		SET_BIT(DDRC,Pin);
			break;

		case DIO_PORTD:
		SET_BIT(DDRD,Pin);
			break;

		default :
			break;
	}
		break;

		case DIO_PIN_INPUT:
			switch(Port)

			{
			case DIO_PORTA:
		CLR_BIT(DDRA,Pin);
			break;

			case DIO_PORTB:
			CLR_BIT(DDRB,Pin);
				break;

			case DIO_PORTC:
			CLR_BIT(DDRC,Pin);
				break;

			case DIO_PORTD:
			CLR_BIT(DDRD,Pin);
				break;

			default :
				break;

}
	}
}

/*
	Function Name        : DIO_SetPortVal
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8 Val
	Function Description : set the value of port
*/
void DIO_SetPortVal(uint8 Port , uint8 Val)
{
	switch (Port)
		{
		case DIO_PORTA :
			PORTA = Val ;
		break;
		case DIO_PORTB :
			PORTB = Val ;
			break;
		case DIO_PORTC :
			PORTC = Val ;
			break;
		case DIO_PORTD :
			PORTD = Val ;
			break;
		default :
			break;
		}
}

/*
	Function Name        : DIO_SetPinVal
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8 Pin    ,uint8 Val
	Function Description : set the value of pin
*/
void DIO_SetPinVal( uint8 Port , uint8 Pin    ,uint8 Val  )
{
	switch (Val)
		{
		case DIO_PIN_HIGH:
			switch(Port)

			{
			case DIO_PORTA:
		SET_BIT(PORTA,Pin);
			break;

			case DIO_PORTB:
			SET_BIT(PORTB,Pin);
				break;

			case DIO_PORTC:
			SET_BIT(PORTC,Pin);
				break;

			case DIO_PORTD:
			SET_BIT(PORTD,Pin);
				break;

			default :
				break;
		}
			break;

			case DIO_PIN_LOW:
				switch(Port)

				{
				case DIO_PORTA:
			CLR_BIT(PORTA,Pin);
				break;

				case DIO_PORTB:
				CLR_BIT(PORTB,Pin);
					break;

				case DIO_PORTC:
				CLR_BIT(PORTC,Pin);
					break;

				case DIO_PORTD:
				CLR_BIT(PORTD,Pin);
					break;

				default :
					break;

	}
		}
}

/*
	Function Name        : DIO_ReadPort
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8* Val
	Function Description : read the value of port
*/
void DIO_ReadPort(uint8 Port , uint8* Val)
{
	switch (Port)
			{
			case DIO_PORTA :
				*Val=PINA ;
			break;
			case DIO_PORTB :
				*Val = PINB ;
				break;
			case DIO_PORTC :
				*Val = PINC ;
				break;
			case DIO_PORTD :
				*Val = PIND ;
				break;
			default :
				break;
			}
}

/*
	Function Name        : DIO_ReadPin
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8 Pin    ,uint8* Val 
	Function Description : read the value of pin
*/
void DIO_ReadPin( uint8 Port , uint8 Pin    ,uint8* Val    )
{
	switch (Port)
				{
				case DIO_PORTA :
					*Val= GET_BIT(PINA,Pin);
				break;
				case DIO_PORTB :
					*Val = GET_BIT(PINB,Pin);
					break;
				case DIO_PORTC :
					*Val = GET_BIT(PINC,Pin);
					break;
				case DIO_PORTD :
					*Val = GET_BIT(PIND,Pin);
					break;
				default :
					break;
				}
}


/*
	Function Name        : DIO_TogglePin
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8 Pin
	Function Description : reverse the value of pin
*/
void DIO_TogglePin(uint8 Port , uint8 Pin)
{
	switch(Port)

					{
					case DIO_PORTA:
				TOGGLE_BIT(PORTA,Pin);
					break;

					case DIO_PORTB:
					TOGGLE_BIT(PORTB,Pin);
						break;

					case DIO_PORTC:
					TOGGLE_BIT(PORTC,Pin);
						break;

					case DIO_PORTD:
					TOGGLE_BIT(PORTD,Pin);
						break;

					default :
						break;

		}
}

/*
	Function Name        : SET_PULL_UP_RESESTOR
	Function Returns     : void
	Function Arguments   : uint8 Port , uint8 Pin
	Function Description : set pull_up_resestor of pin
*/

void SET_PULL_UP_RESESTOR(uint8	DIO_PORT ,uint8 DIO_PIN)
{
	switch (DIO_PORT)
	{
		case DIO_PORTA:
		SET_BIT(PORTA ,DIO_PIN);
		break;
		
		case DIO_PORTB:
		SET_BIT(PORTB ,DIO_PIN);
		break;
		
		case DIO_PORTC:
		SET_BIT(PORTC ,DIO_PIN);
		break;
		
		case DIO_PORTD:
		SET_BIT(PORTD ,DIO_PIN);
		break;
		
		default:
		break;
	}
}