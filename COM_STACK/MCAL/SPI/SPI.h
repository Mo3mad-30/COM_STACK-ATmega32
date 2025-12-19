#ifndef SPI_H
#define SPI_H
#include <stdint.h>
#include "Port.h"
#include "Port_cfg.h"
#include <stdbool.h>

#define SPCR_BASE_ADDRESS 0x2D
#define SPDR_BASE_ADDRESS 0x2F
#define SPSR_BASE_ADDRESS 0x2E
//#define MCUCR_BASE_ADDRESS 0x55

#define SPCR (*(volatile uint8_t *)SPCR_BASE_ADDRESS)
#define SPDR (*(volatile uint8_t *)SPDR_BASE_ADDRESS)
#define SPSR (*(volatile uint8_t *)SPSR_BASE_ADDRESS)
//#define MCUCR (*(volatile uint8_t *)MCUCR_BASE_ADDRESS)

// SPCR bits
#define SPIE  7
#define SPE   6
#define DORD  5
#define MSTR  4
#define CPOL  3
#define CPHA  2
#define SPR1  1
#define SPR0  0

// SPSR bits
#define SPIF  7

typedef enum{
    SPI_CLK_4,
    SPI_CLK_16,
    SPI_CLK_64,
    SPI_CLK_128
} SPI_CLOCK_RATE;

typedef enum {
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3
} SPI_MODE;

typedef enum{
    SPI_MSB,
    SPI_LSB
} SPI_DATA_ORDER;

void SPI_CFG (SPI_MODE spi_mode , SPI_DATA_ORDER spi_dord );
//Configure SPI mode and data order (MSB/LSB first)
void SPI_MasterInit(SPI_CLOCK_RATE spi_clk);
void SPI_SlaveInit(void);
//Initialize SPI as Master or Slave
void SPI_MasterTransmit(uint8_t data);    
void SPI_MasterTransmitString(uint8_t* string);
//Transmit a byte or a string through SPI
uint8_t SPI_GetReceived(void);         
uint8_t* SPI_ReceiveString(void);  
//Receive a byte or a string through SPI 

void __vector_12(void) __attribute__ ((signal, used));  

#endif
