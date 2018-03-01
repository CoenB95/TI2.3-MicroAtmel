/*
 * Week 1.c
 *
 * Created: 1-3-2018 12:52:45
 * Author : coenb
 */ 

#include <avr/io.h>
#include "main.h"
#include "wait.h"

int main(void)
{
	//Select the assignment you want to see executed:
	
	//Week1_assignment2();
	Week1_assignment3();
    //Week1_assignment5();
}

void Week1_assignment2()
{
	//Set all PORTD to act as outputs
	DDRD = 0xFF;
	
	while (1)
	{
		wait(500);
		PORTD |= (1 << 7);
			
		wait(500);
		PORTD &= ~(1 << 7);
	}
}

void Week1_assignment3()
{
	int pinHoog = 0;

	//Set all PORTC to act as inputs
	DDRC = 0x00;

	//Set all PORTD to act as outputs
	DDRD = 0xFF;
	
	while (1)
	{
		if(!(PINC & 0x01))
		{
			if(!pinHoog)
			{
				PORTD |= (1 << 7);
				pinHoog = 1;
			}
			else
			{
				PORTD &= ~(1 << 7);
				pinHoog = 0;
			}
		}
		wait(500);
	}
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
