/*
 * Week 4 - spi.h
 *
 * Created: 7-3-2018 13:17:14
 *  Author: Coen Boelhouwers, Sander de Nooijer
 */ 


#ifndef SPI_H_
#define SPI_H_

#define BIT(x)		( 1<<x )
#define DDR_SPI		DDRB		// spi Data direction register
#define PORT_SPI	PORTB		// spi Output register
#define SPI_SCK		1		// PB1: spi Pin System Clock
#define SPI_MOSI	2		// PB2: spi Pin MOSI
#define SPI_MISO	3		// PB3: spi Pin MISO
#define SPI_SS		0		// PB0: spi Pin Slave Select

void spi_masterInit(void);
void spi_write(unsigned char);
char spi_writeRead( unsigned char);
void spi_slaveSelect(unsigned char);
void spi_slaveDeSelect(unsigned char);

#endif /* SPI_H_ */