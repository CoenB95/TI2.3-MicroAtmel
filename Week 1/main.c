/*
 * Week 1 - main.c
 *
 * Created: 1-3-2018 12:52:45
 * Author : Coen Boelhouwers, Sander de Nooijer
 */ 

#define STATE_1HZ 1
#define STATE_4HZ 4

#include <avr/io.h>
#include "main.h"
#include "wait.h"

int main(void)
{
	//Select the assignment you want to see executed:
	
	//Week1_assignment2();
	//Week1_assignment3();
	//Week1_assignment4();
    //Week1_assignment5();
	//Week1_assignment6();
	Week1_assignment7b();
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


void Week1_assignment4()
{
	DDRD = 0xFF;
	int currentlight = 0;	
	while(1)
	{
		currentlight = (currentlight + 1) % 8 ;
		
		PORTD |= (1 << currentlight);
		if(currentlight > 0)
		{
		PORTD &= ~(1 << (currentlight - 1));		
		}
		else
		{
		PORTD &= ~(1 << 7);
		}
		wait(50);
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

void Week1_assignment6()
{
	int state = STATE_1HZ;
	int timer = 0;
	
	//Set all PORTC to act as inputs
	DDRC = 0x00;

	//Set all PORTD to act as outputs
	DDRD = 0xFF;
	
	while(1)
	{
		if (PINC & 0x01)
		{
			switch(state)
			{
				case STATE_1HZ:
					state = STATE_4HZ;
					break;
				case STATE_4HZ:
					state = STATE_1HZ;
					break;
			}
		}
		
		wait(10);
		timer -= 10;
		
		if(timer <= 0)
		{
			PORTD ^= 0x80;
		
			switch(state)
			{
				case STATE_1HZ:
					timer = 1000;
					break;
				case STATE_4HZ:
					timer = 250;
					break;
			}
		}
	}
}

void Week1_assignment7b()
{
	int led = 0; 
	//Set all PORTD to act as inputs
	DDRD = 0x00;		
		
	while(1)
	{
		led = (led + 1) % 6;
		setCharlieLed(led);
		wait(500);
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

void setCharlieLed(int lednr)
{	
	switch (lednr)
	{
		case 0:
			DDRD = 0b110;
			PORTD = 0b100;
			break;
		case 1:
			DDRD = 0b110;
			PORTD = 0b010;
			break;
		case 2:
			DDRD = 0b011;
			PORTD = 0b010;
			break;
		case 3:
			DDRD = 0b011;
			PORTD = 0b001;
			break;
		case 4:
			DDRD = 0b101;
			PORTD = 0b001;
			break;
		case 5:
			DDRD = 0b101;
			PORTD = 0b100;
			break;
	}
}

