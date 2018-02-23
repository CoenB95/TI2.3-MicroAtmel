/*
 * lcd.h
 *
 * Created: 23-2-2018 10:47:32
 *  Author: Coen Boelhouwers and Sander de Nooijer
 */ 


#ifndef LCD_H_
#define LCD_H_

static const int LINE0_START = 0x00;
static const int LINE1_START = 0x40;

typedef struct {
	//true if 8bits, false if 4bits.
	int bitMode8;
	int displayEnabled;
	int cursorEnabled;
	int cursorBlinking;
} Display;

void LCD_clear();
void LCD_init();
void LCD_moveHome();
void LCD_setCursor(int);
void LCD_setDisplayEnabled(int);
void LCD_setPosition(int);
void LCD_shiftLeft();
void LCD_writeString(char[]);
void LCD_writeStringAtPosition(int, char[]);

#endif /* LCD_H_ */