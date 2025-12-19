#ifndef COMM_H
#define COMM_H
#include "SPI.h"
#include "UART.h"
#include "Port.h"
#include "Port_cfg.h"

void COMM_UART_Init( UART_BAUD_RATE baud);
void COMM_SPI_Init(SPI_MODE mode , SPI_DATA_ORDER dord , SPI_CLOCK_RATE clk);

#endif