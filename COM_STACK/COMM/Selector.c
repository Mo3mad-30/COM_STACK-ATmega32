//this is meant to  help the user select the communication protocol : spi or uart

#include "stdint.h"
#include "SPI.h"
#include "UART.h"
#include "Port.h"
#include "Port_cfg.h"
#include "Comm.h"

#define UART_PROT 1
#define SPI_PROT 2
#define SELECTED_MODE SPI_PROT //change this before running

void Select_Protocol(UART_BAUD_RATE baud , SPI_CLOCK_RATE clk , SPI_MODE mode , SPI_DATA_ORDER dord) {
    if (SELECTED_MODE == UART_PROT){
        COMM_UART_Init(baud);
    }
    else if (SELECTED_MODE == SPI_PROT){
        COMM_SPI_Init(mode ,dord ,clk);
    }
}


uint8_t SEL_ReceiveByte(void){
     if (SELECTED_MODE == UART_PROT){
        return UART_Receive();
    }
    else if (SELECTED_MODE == SPI_PROT){
        return SPI_GetReceived();
    }
    else{
        return 0; 
    }

}

uint8_t* SEL_ReceiveString(void){
     if (SELECTED_MODE == UART_PROT){
        return UART_ReceiveString();
    }
    else if (SELECTED_MODE == SPI_PROT){
        return SPI_ReceiveString();
    }
    else{
        return (uint8_t*)0; 
    }

}

void SEL_TransmitByte(uint8_t byte){
    if (SELECTED_MODE == UART_PROT){
        UART_Transmit(byte);
    }
    else if (SELECTED_MODE == SPI_PROT){
        SPI_MasterTransmit(byte);
    }
}

void SEL_TransmitString(uint8_t* string){
    if (SELECTED_MODE == UART_PROT){
        UART_TransmitString(string);
    }
    else if (SELECTED_MODE == SPI_PROT){
        SPI_MasterTransmitString(string);
    }
}