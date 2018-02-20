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


int x = 0;
int hxx = 8;
int xx;
int nextTrigger = 0;

ISR ( INT1_vect )
{
	if (nextTrigger == 0)
	{
		nextTrigger = 1;
		stepTaillight();
	}
	//if(x > 7 )
	//{
		//x = 4;
	//}
	//PORTD |= (1<<x);
}

ISR ( INT2_vect )
{
	if (nextTrigger == 1)
	{
		nextTrigger = 0;
		stepTaillight();
	}
	//PORTD &= ~(1<<x);
	//x++;
	//if(x > 7)
	//{
		//x = 4;
	//}	
}


void Week2_asignment2()
{
	xx = hxx * 2;
	x = xx - 1;
	
	DDRD = 0x00;
	DDRE = 0xFF;
	
	EICRA |= 0x2C;
	EIMSK |= 0x06;
	
	sei();
	
	while (1)
	{
		
	}
}

void main()
{
	Week2_asignment2();	
	
}

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
