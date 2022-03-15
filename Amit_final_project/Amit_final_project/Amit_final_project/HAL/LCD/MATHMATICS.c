/*
 * MATHMATICS.c
 *
 * Created: 11/10/2021 7:28:05 PM
 *  Author: alkods
 */ 



#include "MATHMATICS.h"

uint32 Pow_int(uint32 NUM, uint8 POWER)
{
	uint32 RESULT = 1;
	for (uint8 i=0;i<POWER;i++)
	{
		RESULT=RESULT*NUM;
	}
	return RESULT;
}


f32 Pow_float(f32 NUM, uint8 POWER)
{
	f32 RESULT = 1;
	for (uint8 i=0;i<POWER;i++)
	{
		RESULT=RESULT*NUM;
	}
	return RESULT;
}

