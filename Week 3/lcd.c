/*
 * Week 3 - lcd.c
 *
 * Created: 23-2-2018 10:47:20
 *  Author: Coen Boelhouwers, Sander de Nooijer
 */ 
#include <avr/io.h>
#include "lcd.h"
#include "wait.h"

void LCD_toggleE();
void LCD_write(int, char);
void LCD_writeCommand(char);
void LCD_writeCharacter(char);
void LCD_writeDisplay();

static const char LCD_DATA_MASK = 0xF0;
static const char LCD_RS_SHIFT = 2;
static const char LCD_E_SHIFT = 3;

Display display = {
	1 //8bit mode at start.
};



void LCD_clear()
{
	LCD_writeCommand(0x01);
}

void LCD_init()
{
	//Set all of PORTC to outputs.
	DDRC = 0xFF;
	
	wait(2000);
	
	//Set display to 4bit-mode
	LCD_writeCommand(0x28);
	display.bitMode8 = 0;
	
	wait(50);
	
	//Resend (now 4bit) for number of lines and font.
	LCD_writeCommand(0x28);
	
	wait(50);
	
	//Home
	LCD_moveHome();
	
	//Display on, cursor off, cursor blinking off
	display.displayEnabled = 1;
	display.cursorEnabled = 0;
	display.cursorBlinking = 0;
	LCD_writeDisplay();
	
	//Cursor increment
	LCD_writeCommand(0x06);
	
	LCD_clear();
	LCD_setPosition(0);
}

void LCD_moveHome()
{
	LCD_writeCommand(0x02);
}

void LCD_setCursor(int position)
{
	
}

void LCD_setDisplayEnabled(int value)
{
	display.displayEnabled = value;
	LCD_writeDisplay();
}

void LCD_setPosition(int position)
{
	LCD_writeCommand(0x80 | (0x7F & position));
}

void LCD_shiftLeft()
{
	LCD_writeCommand(0x18);
}

void LCD_toggleE()
{
	PORTC |= (1<<LCD_E_SHIFT);
	wait(1);
	PORTC &= ~(1<<LCD_E_SHIFT);
	wait(1);
}

void LCD_write(int rs, char command)
{
	if (rs)
		PORTC |= (1<<LCD_RS_SHIFT);
	else
		PORTC &= ~(1<<LCD_RS_SHIFT);
	
	PORTC &= ~(LCD_DATA_MASK); //Reset bits
	PORTC |= (LCD_DATA_MASK & command); //Set bits
	LCD_toggleE();
	if (!display.bitMode8)
	{
		//4 bits mode - send two portions.
		PORTC &= ~(LCD_DATA_MASK); //Reset bits
		PORTC |= (LCD_DATA_MASK & (command<<4)); //Set bits
		LCD_toggleE();
	}
}

void LCD_writeCharacter(char character)
{
	LCD_write(1, character);
}

void LCD_writeCommand(char command)
{
	LCD_write(0, command);
}

void LCD_writeDisplay()
{
	char val = 0x08;
	val |= (display.displayEnabled<<2);
	val |= (display.cursorEnabled<<1);
	val |= (display.cursorBlinking<<0);
	LCD_writeCommand(val);
}

void LCD_writeString(char* message)
{
	while(*message)
		LCD_writeCharacter(*(message++));
}

void LCD_writeStringAtPosition(int position, char* message)
{
	LCD_setPosition(position);
	LCD_writeString(message);
}