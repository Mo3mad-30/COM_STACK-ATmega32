#define F_CPU 8000000UL  

#include "SPI.h"
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "Port.h"
#include "Port_cfg.h"

//for string transmission
#define SPI_TX_Max_len 64

volatile uint8_t SPI_TX_Buffer [SPI_TX_Max_len];
volatile uint8_t SPI_TX_Index = 0;
volatile uint8_t SPI_TX_string_length = 0;
volatile bool TX_busy_flag = false;

//for string reception
#define SPI_RX_Max_len 64

volatile uint8_t SPI_RX_Buffer[SPI_RX_Max_len];
volatile uint8_t SPI_RX_Index = 0;
volatile bool SPI_RX_done_flag = false;

volatile uint8_t spi_received_data;



static inline void sei_asm(void){
    __asm__ __volatile__ ("sei" ::: "memory");
}

void SPI_CFG(SPI_MODE spi_mode , SPI_DATA_ORDER spi_dord ){
//clear mode bits then set them
    SPCR &= ~((1 << CPOL) | (1 << CPHA));
    switch (spi_mode)
    {
    case SPI_MODE_0: break;
    case SPI_MODE_1: SPCR |= (1 << CPHA); break;
    case SPI_MODE_2: SPCR |= (1 << CPOL); break;
    case SPI_MODE_3: SPCR |= (1 << CPOL) | (1 << CPHA); break;
    }

//clear order bits then set them
    SPCR &= ~(1 << DORD);
    switch (spi_dord)
    {
    case SPI_MSB: break;
    case SPI_LSB: SPCR |= (1 << DORD); break;
    }
}

void SPI_MasterInit(SPI_CLOCK_RATE spi_clk){


    Port_SetPinDirection(PORT_B, OUTPUT, 5); // MOSI
    Port_SetPinDirection(PORT_B, OUTPUT, 7); // SCK
    Port_SetPinDirection(PORT_B, OUTPUT, 4); // SS
    Port_SetPinDirection(PORT_B, INPUT,  6); // SPE
    

    // SS high
    Port_SetPinChannelValue(PORT_B, HIGH, 4);

    SPCR &= ~((1<<SPR1)|(1<<SPR0)); //clear clock rate bits




    // Clock rates
    switch (spi_clk)
    {
    case SPI_CLK_4:
        break;
    case SPI_CLK_16:
        SPCR |= (1 << SPR0);
        break;
    case SPI_CLK_64:
        SPCR |= (1 << SPR1);
        break;
    case SPI_CLK_128:
        SPCR |= (1 << SPR1) | (1 << SPR0);
        break;
    }

    
    // Enable SPI  ,master
    SPCR |= (1 << SPE) | (1 << MSTR);

    // Enable SPI interrupt
    SPCR |= (1 << SPIE);

    sei_asm();
}

void SPI_SlaveInit(void){

    SPCR &= ~(1<<MSTR);   //clear maser bit

    Port_SetPinDirection(PORT_B, INPUT,  4); // SS
    Port_SetPinDirection(PORT_B, INPUT,  5); // MOSI
    Port_SetPinDirection(PORT_B, OUTPUT, 6); // MISO
    Port_SetPinDirection(PORT_B, INPUT,  7); // SCK

    // Enable SPI , interrupt
    SPCR |= (1 << SPE) | (1 << SPIE);

    sei_asm();
}

uint8_t SPI_GetReceived(void){
    return spi_received_data;
}

uint8_t* SPI_ReceiveString(void){

    if(SPI_RX_done_flag == true){
        SPI_RX_done_flag = false;
        return (uint8_t*)SPI_RX_Buffer;
    }

    return (uint8_t*)0; 

}

void SPI_MasterTransmit(uint8_t data){

    if(TX_busy_flag){
        return;
    }
   
    TX_busy_flag = true;
    Port_SetPinChannelValue(PORT_B, LOW, 4);

    SPDR = data;            

}

void SPI_MasterTransmitString(uint8_t* string){
    if (TX_busy_flag){
        return; 
    }

    TX_busy_flag= true;
    SPI_TX_string_length = 0;

    while(SPI_TX_string_length < SPI_TX_Max_len -1  && string[SPI_TX_string_length]){
        SPI_TX_Buffer[SPI_TX_string_length] = string[SPI_TX_string_length];
        SPI_TX_string_length++;
    }

    SPI_TX_Buffer[SPI_TX_string_length] = '\0';
    SPI_TX_string_length++;
    SPI_TX_Index = 1;
    Port_SetPinChannelValue(PORT_B, LOW, 4); 
    SPDR = SPI_TX_Buffer[0]; // start transmission with the first byte
}

void __vector_12(void){

    volatile uint8_t clear  = SPSR;
    volatile uint8_t data = SPDR;

    spi_received_data = data; 

    //handle receive string

    if (!SPI_RX_done_flag){
        if (data =='\0' || SPI_RX_Index >= SPI_RX_Max_len - 1){
            SPI_RX_Buffer[SPI_RX_Index] = '\0';
            SPI_RX_Index = 0; // reset
            SPI_RX_done_flag = true;
        }
        else{
            SPI_RX_Buffer[SPI_RX_Index++] = data;
        }
    }

    //handle transmit string

    if (TX_busy_flag)
    {
        if(SPI_TX_Index < SPI_TX_string_length){
            SPDR = SPI_TX_Buffer[SPI_TX_Index++];
        }
 
        else {
            TX_busy_flag = false;
            Port_SetPinChannelValue(PORT_B, HIGH, 4); 
        }
    }
    
}
