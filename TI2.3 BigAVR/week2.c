/*
 * week2.c
 *
 * Created: 20-2-2018 10:33:25
 *  Author: sander
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "week2.h"

#define MAX_NUMBERS 16

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

const int DEFAULT_DELAY = 200;
const unsigned char NUMBER_ERROR = 0b01000000; //-
const unsigned char NUMBER_MAPPING[MAX_NUMBERS] =
{
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // b
	0b00111001, // C
	0b01011110, // d
	0b01111001, // E
	0b01110001, // F
};

//The assignment that's currently active. Used for switching in interrupts.
int activeAssignment;

//Due to push button bouncing, we use a slight delay until accepting a new button-press.
int interruptDelay = 0;

//Variables for assignment 2
int x = 0;
int hxx = 8;
int xx;
int nextTrigger = 0;

//Variables for assignment 3
int currentValue = 0;

ISR ( INT1_vect )
{
	if (!interruptDelay)
	{
		interruptDelay = DEFAULT_DELAY;
		switch (activeAssignment)
		{
			case 2:
				if (nextTrigger == 0)
				{
					nextTrigger = 1;
					stepTaillight();
				}
				break;
			case 3:
				currentValue++;
				displayNumber(currentValue);
				break;
		}
	}
}

ISR ( INT2_vect )
{
	if (!interruptDelay)
	{
		interruptDelay = DEFAULT_DELAY;
		switch (activeAssignment)
		{
			case 2:
				if (nextTrigger == 1)
				{
					nextTrigger = 0;
					stepTaillight();
				}
				break;
			case 3:
				currentValue--;
				displayNumber(currentValue);
				break;
		}
	}
}

void main()
{
	//Select the assignment you want to see:
	
	//Week2_asignment2();
	Week2_asignment3();
}

/*
  Runs a chaser-effect on the leds connected to PORT-E.
  The chaser effect can be controlled by buttons on PORTD.1 and PORTD.2.
  PORTD.1 triggers one step of the chase effect on it's rising edge, while
  PORTD.2 triggers one step of the chase effect on it's falling edge.
*/
void Week2_asignment2()
{
	activeAssignment = 2;
	xx = hxx * 2;
	x = xx - 1;
	
	//INT_1 is connected to PORTD.1.
	//INT_2 is connected to PORTD.2.
	
	//Set all PORTD ports to act as inputs.
	DDRD = 0x00;
	
	//Set all PORTE ports to act as outputs.
	DDRE = 0xFF;
	
	//Set INT_1's mode to rising-edge: 0b----_11--
	//Set INT_2's mode to falling-edge: 0b--10_----
	EICRA |= 0x2C;
	
	//Enable INT_1 and INT_2: 0b----_-11-
	EIMSK |= 0x06;
	
	//Enable global interrupts.
	sei();
	
	while (1)
	{
		//Do nothing, program flow is determined by button presses interrupts.
	}
}

/** \brief Step chaser-effect

    Executes a single step in a chaser-effect over the leds of PORTE.
	The method uses a single integer value to keep hold of the state, counting from zero to double the amount of leds.
	That is because on the first run all leds are turned on one by one, and after that they need to be turned off.
 */
void stepTaillight() {
	x = (x + 1)%xx;
	if (x < hxx)
	{
		int i;
		for (i = 0; i < hxx; i++)
		{
			PORTE |= ((x>=i) << i);
		}
	}
	else
	{
		int x2 = x%hxx;
		int i;
		for (i = 0; i < hxx; i++)
		{
			PORTE &= ~((x2>=i) << i);
		}
	}
}

void Week2_asignment3()
{	
	activeAssignment = 3;
	
	//INT_1 is connected to PORTD.1 and acts as "UP".
	//INT_2 is connected to PORTD.2 and acts as "DOWN".
	//Pressing both resets the digit.
	
	//Set all PORTD ports to act as inputs.
	DDRD = 0x00;
	
	//Set all PORTE ports to act as outputs.
	DDRE = 0xFF;
	
	//Set both INT_1 and INT_2's mode to rising-edge: 0b----_11--
	EICRA = 0x3C;
	
	//Enable INT_1 and INT_2: 0b----_-11-
	EIMSK |= 0x06;
	
	//Enable global interrupts.
	sei();
	
	currentValue = 5;
	displayNumber(currentValue);
	
	while (1)
	{
		//Do nothing, program flow is determined by button presses interrupts.
		if (interruptDelay > 0)
		{
			interruptDelay--;
		}
		wait(1);
	}
}

void displayNumber(int digit)
{
	if (digit < 0 || digit >= MAX_NUMBERS)
	{
		PORTE = NUMBER_ERROR;
	}
	else
	{
		PORTE = NUMBER_MAPPING[digit];
	}
}