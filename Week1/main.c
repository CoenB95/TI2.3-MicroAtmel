/*
 * Week1.c
 *
 * Created: 1-3-2018 12:35:04
 * Author : sander
 */ 

#include <avr/io.h>
#include "wait.h"


int main(void)
{
	DDRD = 0xFF; //set all PORTD to acts as outputs
	DDRC = 0x00; //set all PORTC to accts as inputs
	int pinHoog = 0;
	PORTC = 0x01;
	

    while (1) 
    {
		if(!(PINC & 0x01))
		{ //opdracht 1 
			if(!pinHoog)
				{
				wait(500);
				PORTD |= (1 << 7);
				pinHoog = 1;
				}
			else
				{
				wait(500);
				PORTD &= ~(1 << 7);
				pinHoog = 0;	
				}
		}
		else
			{
			
			}
		
		
    }
}

