/*
 * main.h
 *
 * Created: 1-3-2018 12:55:39
 *  Author: coenb
 */ 


#ifndef MAIN_H_
#define MAIN_H_

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
void Week1_assignment5(void);
void runPattern(PatternPart*);

#endif /* MAIN_H_ */