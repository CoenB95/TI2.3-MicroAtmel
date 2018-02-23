/*
 * Week 3.c
 *
 * Created: 23-2-2018 10:46:33
 * Author : Coen Boelhouwers and Sander de Nooijer
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "wait.h"

int main(void)
{
	LCD_init();
	LCD_writeString("Hallo allemaal,");
	LCD_writeStringAtPosition(LINE1_START, "              wat fijn dat je er bent...");
	//LCD_writeStringAtPosition(LINE1_START, "Allemaal!");
	
	DDRE = 0xFF;
	PORTE = 0b10101010;
	
    /* Replace with your application code */
    while (1) 
    {
		wait(500);
		LCD_shiftLeft();
    }
}

