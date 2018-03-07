/*
 * Week 4 - main.c
 *
 * Created: 7-3-2018 11:31:57
 * Author : Coen Boelhouwers, Sander de Nooijer
 */ 

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "main.h"
#include "wait.h"
#include "lcd.h"

int main(void)
{
    //Select the assignment you want to see executed:
    
	//Week4_assignment1();
    //Week4_assignment2();
    Week4_assignment3();
    //Week4_assignment4();
    //Week4_assignment5();
    //Week4_assignment6();
    //Week1_assignment7b();
}

void Week4_assignment1()
{  
	ADMUX =  0b01100000; //[4.0]Vref = Vcc, [5]left-adjusted 
	ADCSRA = 0b11100110; //[2.0]Prescaler = 64, [5]freerunning, [6]start, [7]enabled
	
	//Set all PORTA to act as outputs
	DDRA = 0xFF;
	
	//Set all PORTB to act as outputs
	DDRB = 0xFF;
	
	//Set all PORTF to act as inputs
	DDRF = 0x00;
		
	while(1)
	{
		PORTA = ADCH;
		PORTB = ADCL;
	}
}

void Week4_assignment2()
{
	ADMUX =  0b01100011; //[6.7]Vref = Vcc, [5]left-adjusted,[4.0] channel = ADC3
	ADCSRA = 0b10000110; //[2.0]Prescaler = 64, [5]freerunning, [6]start, [7]enabled
	
	//Set all PORTA to act as outputs
	DDRA = 0xFF;
	
	//Set all PORTB to act as outputs
	DDRB = 0xFF;
	
	//Set all PORTF to act as inputs
	DDRF = 0x00;
	
	while(1)
	{
		ADCSRA |= (1 << 6);
		while(ADCSRA & (1 << 6));
		PORTA = ADCH;
		wait(500);
	}
}

void Week4_assignment3()
{
	ADMUX =  0b11100001; //[6.7]Vref = Vcc, [5]left-adjusted,[4.0] channel = ADC3
	ADCSRA = 0b10000110; //[2.0]Prescaler = 64, [5]freerunning, [6]start, [7]enabled
	
	//Set all PORTA to act as outputs
	DDRA = 0xFF;
	
	//Set all PORTB to act as outputs
	DDRB = 0xFF;
	
	//Set all PORTF to act as inputs
	DDRF = 0x00;
			
			LCD_init();
					ADCSRA |= (1 << 6);
					while(ADCSRA & (1 << 6));
					PORTA = ADCH;
					//INT_1 is connected to PORTD.1.
					//INT_2 is connected to PORTD.2.
					
					//Set all PORTD ports to act as inputs.
					DDRD = 0xFF;
					//Set all PORTE ports to act as outputs.
					DDRE = 0xFF;
					
					//Set INT_1's mode to rising-edge: 0b----_11--
					//Set INT_2's mode to falling-edge: 0b--10_----
					EICRA |= 0x2C;
					
					//Enable INT_1 and INT_2: 0b----_-11-
					EIMSK |= 0x06;
					
					//Enable global interrupts.
					sei();
					int temperatuur = 0;

	while(1)
	{
		ADCSRA |= (1 << 6);
		while(ADCSRA & (1 << 6));
		PORTA = ADCH;
		char string[20];
		temperatuur = ADCH;
		snprintf(string, 20, "temperatuur: %d", temperatuur);
	    LCD_writeStringAtPosition(LINE1_START, string);
		wait(500);
	}
}

