/*
 * Week 1.c
 *
 * Created: 1-3-2018 12:52:45
 * Author : coenb
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	//Select the assignment you want to see executed:
	
    Week1_assignment5();
}

void Week1_assignment5()
{
	//Set all PORTD ports to act as outputs.
	DDRD = 0xFF;
	
	while(1)
	{
		runPattern(knightRiderPattern);
	}
}

void runPattern(PatternPart* pattern)
{
	int index = 0;
	
	while(pattern[index].delay != 0)
	{
		PORTD = pattern[index].data;
		wait(pattern[index].delay);
		index++;
	}
}

