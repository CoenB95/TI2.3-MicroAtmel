/*
 * wait.c
 *
 * Created: 23-2-2018 12:40:01
 *  Author: coenb
 */ 
#define F_CPU 8000000

#include <util/delay.h>

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}