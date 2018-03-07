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
#include "spi.h"

int main(void)
{
    //Select the assignment you want to see executed:
    
	//Week4_assignment1();
    //Week4_assignment2();
    //Week4_assignment3();
    Week4_assignment4();
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

void Week4_assignment4()
{
	DDRB=0x01;					// Set PB0 pin as output for display select
	spi_masterInit();              	// Initialize spi module
	displayDriverInit();            // Initialize display chip

	// clear display (all zero's)
	for (char i =1; i<=4; i++)
	{
		spi_slaveSelect(0); 		// Select display chip
		spi_write(i);  			// 	digit adress: (digit place)
		spi_write(0);			// 	digit value: 0
		spi_slaveDeSelect(0);	// Deselect display chip
	}
	wait(1000);
	
	// write 4-digit data
	for (char i =1; i<=4; i++)
	{
		spi_slaveSelect(0);       // Select display chip
		spi_write(i);         	// 	digit adress: (digit place)
		spi_write(i);  			// 	digit value: i (= digit place)
		spi_slaveDeSelect(0); 		// Deselect display chip
		
		wait(1000);
	}
	wait(1000);
}

// Initialize the driver chip (type MAX 7219)
void displayDriverInit() 
{
	spi_slaveSelect(0);			// Select display chip (MAX7219)
  	spi_write(0x09);      		// Register 09: Decode Mode
  	spi_write(0xFF);			// 	-> 1's = BCD mode for all digits
  	spi_slaveDeSelect(0);		// Deselect display chip

  	spi_slaveSelect(0);			// Select dispaly chip
  	spi_write(0x0A);      		// Register 0A: Intensity
  	spi_write(0x0F);    			//  -> Level 4 (in range [1..F])
  	spi_slaveDeSelect(0);		// Deselect display chip

  	spi_slaveSelect(0);			// Select display chip
  	spi_write(0x0B);  			// Register 0B: Scan-limit
  	spi_write(0x03);   			// 	-> 1 = Display digits 0..1
  	spi_slaveDeSelect(0);		// Deselect display chip

  	spi_slaveSelect(0);			// Select display chip
  	spi_write(0x0C); 			// Register 0B: Shutdown register
  	spi_write(0x01); 			// 	-> 1 = Normal operation
  	spi_slaveDeSelect(0);		// Deselect display chip
}

// Set display on ('normal operation')
void displayOn() 
{
  	spi_slaveSelect(0);			// Select display chip
  	spi_write(0x0C); 			// Register 0B: Shutdown register
  	spi_write(0x01); 			// 	-> 1 = Normal operation
  	spi_slaveDeSelect(0);		// Deselect display chip
}

// Set display off ('shut down')
void displayOff() 
{
  	spi_slaveSelect(0);			// Select display chip
  	spi_write(0x0C); 			// Register 0B: Shutdown register
  	spi_write(0x00); 			// 	-> 1 = Normal operation
  	spi_slaveDeSelect(0);		// Deselect display chip
} 
