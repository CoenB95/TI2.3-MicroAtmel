/*
 * Week 3.c
 *
 * Created: 23-2-2018 10:46:33
 * Author : Coen Boelhouwers and Sander de Nooijer
 */ 


#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"
#include "wait.h"

#define BIT(x)			(1 << (x))
//#define F_CPU 8e6



int aantalKeerIngedrukt = 0;
ISR ( INT1_vect )
{
	char string[20];
	aantalKeerIngedrukt++;
	
	snprintf(string, 20, "Aantal: %d", aantalKeerIngedrukt);
	LCD_clear();
	LCD_writeStringAtPosition(0, string);
}

int msCount = 0; //telt de ms
int isHoog = 0; //checkt of het laag of hoog staat
ISR(TIMER2_COMP_vect)
{
	msCount++;	//telt een ms er bij op
	if(msCount == 15 && isHoog) 
	{
		PORTD ^= BIT(7); //toggled het bit
		msCount = 0; //reset the counter
		isHoog = 0; 
	}
	
	if(msCount == 25 && !isHoog)
	{
	 		PORTD ^= BIT(7);
	 		msCount = 0;	
		isHoog = 1;
	}
	
}

void timer2Init(void)
{
	OCR2 = 7;
	TIMSK |= BIT(7);
	SREG |= BIT(7);
	TCCR2 = 0b0001101;
	
	
}

int main(void)
{	
		//INT_1 is connected to PORTD.1.
		//INT_2 is connected to PORTD.2.
		
		//Set all PORTD ports to act as inputs.
		DDRD = 0xFF;
		timer2Init();
		//Set all PORTE ports to act as outputs.
		DDRE = 0xFF;
		
		//Set INT_1's mode to rising-edge: 0b----_11--
		//Set INT_2's mode to falling-edge: 0b--10_----
		EICRA |= 0x2C;
		
		//Enable INT_1 and INT_2: 0b----_-11-
		EIMSK |= 0x06;
		
		//Enable global interrupts.
		sei();
		
	LCD_init();
	LCD_writeString("Hallo allemaal,");
	LCD_writeStringAtPosition(LINE1_START, "              wat fijn dat je er bent...");
	LCD_writeStringAtPosition(LINE1_START, "Allemaal!");
	
	DDRE = 0xFF;
	PORTE = 0b10101010;
	
    /* Replace with your application code */
    while (1) 
    {
		wait(10);
		if(aantalKeerIngedrukt <= 0)
			LCD_shiftLeft();
			
			
    }
}

