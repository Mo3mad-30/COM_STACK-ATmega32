#include "SPI.h"
#include "UART.h"
#include "Port.h"
#include "Port_cfg.h"

void COMM_UART_Init( UART_BAUD_RATE baud){
    Port_Init();
    UART_Init(baud);
}

void COMM_SPI_Init(SPI_MODE mode , SPI_DATA_ORDER dord , SPI_CLOCK_RATE clk){
    Port_Init();
    SPI_CFG(mode , dord);
    SPI_MasterInit(clk);
   // SPI_SlaveInit();
}