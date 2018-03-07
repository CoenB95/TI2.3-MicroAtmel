/*
 * Week 1 - main.h
 *
 * Created: 1-3-2018 12:55:39
 *  Author: Coen Boelhouwers, Sander de Nooijer
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define CHARLIE_HIGH 1
#define CHARLIE_LOW 0
#define CHARLIE_TRI 2

typedef struct {
	int data;
	int delay;	
} PatternPart;

PatternPart knightRiderPattern[] =
{
	{0b00000001, 200},
	{0b00000010, 150},
	{0b00000100, 100},
	{0b00001000, 050},
	{0b00010000, 050},
	{0b00100000, 100},
	{0b01000000, 150},
	{0b10000000, 200},
	{0b01000000, 150},
	{0b00100000, 100},
	{0b00010000, 050},
	{0b00001000, 050},
	{0b00000100, 100},
	{0b00000010, 150},
	{0x00, 0}
};

void Week1_assignment2(void);
void Week1_assignment3(void);
void Week1_assignment4(void);
void Week1_assignment5(void);
void Week1_assignment6(void);
void Week1_assignment7b(void);
void runPattern(PatternPart*);
void setCharlieLed(int);

#endif /* MAIN_H_ */