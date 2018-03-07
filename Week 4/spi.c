/*
 * Week 4 - spi.c
 *
 * Created: 7-3-2018 13:09:45
 *  Author: Coen Boelhouwers, Sander de Nooijer
 */ 

#include <avr/io.h>

#include "spi.h"

void spi_masterInit(void)
{
	DDR_SPI = 0xff;					// All pins output: MOSI, SCK, SS, SS_display
	DDR_SPI &= ~BIT(SPI_MISO);			// 	except: MISO input
	PORT_SPI |= BIT(SPI_SS);			// SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);	// or: SPCR = 0b11010010;
											// Enable spi, MasterMode, Clock rate fck/64
											//  	bitrate=125kHz, Mode = 0: CPOL=0, CPPH=0
}

// Write a byte from master to slave
void spi_write( unsigned char data )				
{
	SPDR = data;					// Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 		// Wait for transmission complete 
}

// Write a byte from master to slave and read a byte from slave - not used here
char spi_writeRead( unsigned char data )
{
	SPDR = data;					// Load byte --> starts transmission
	while( !(SPSR & BIT(SPIF)) ); 		// Wait for transmission complete 
	data = SPDR;					// New received data (eventually, MISO) in SPDR
	return data;					// Return received byte
}

// Select device on pinnumer PORTB
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

void spi_writeSegment(unsigned char address, unsigned char data)
{
	spi_slaveSelect(0);		// Select display chip
	spi_write(address);     // 	digit adress: (digit place)
	spi_write(data);  		// 	digit value: i (= digit place)
	spi_slaveDeSelect(0); 	// Deselect display chip
}

void spi_writeNumber(int value)
{
	if (value < 0)
	{
		value *= -1;
		spi_writeSegment(1, value % 10);
		spi_writeSegment(2, (value/10) % 10);
		spi_writeSegment(3, (value/100) % 10);
		spi_writeSegment(4, 10);
	}
	else
	{
		spi_writeSegment(1, value % 10);
		spi_writeSegment(2, (value/10) % 10);
		spi_writeSegment(3, (value/100) % 10);
		spi_writeSegment(4, (value/1000) % 10);
	}
}
