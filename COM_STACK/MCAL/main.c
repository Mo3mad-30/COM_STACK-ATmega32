#define F_CPU 8000000UL

#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include "Port.h"
#include "Port_cfg.h"
#include "UART.h"
#include "SPI.h"

//test UART receive function

/*int main(void) {
    UART_Init(UART_BAUD_9600);

    Port_Init();

    // Set PD7 as output for LED
    Port_SetPinDirection(PORT_D, OUTPUT, 7);

    while (1) {
        uint8_t received_data = UART_Receive();

        if (received_data == 'H') {
            Port_SetPinChannelValue(PORT_D, HIGH, 7); 
            _delay_ms(500);
            Port_SetPinChannelValue(PORT_D, LOW, 7);  
            _delay_ms(500);
        }
    }
}*/

/*------------------------------------------------------------------------------------------------------------------*/

//test UART transmit function

/*int main(void) {
    UART_Init(UART_BAUD_9600);
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);



    while (1) {
        UART_Transmit('A');  
        Port_SetPinChannelValue(PORT_D, HIGH, 7); 
        _delay_ms(1000);
        Port_SetPinChannelValue(PORT_D, LOW, 7);
        _delay_ms(1000);
    }
}*/

/*--------------------------------------------------------------------------------------------------------------*/

//blinking a led
/*
int main(void){
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);

    while(1){
     Port_SetPinChannelValue(PORT_D, HIGH, 7); 
            _delay_ms(1000);
    Port_SetPinChannelValue(PORT_D, LOW, 7);  
            _delay_ms(2000);
    }

}*/
/*------------------------------------------------------------------------*/

//UART string receive
/*int main(void) {
    UART_Init(UART_BAUD_9600);

    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7); // PD7 LED

    while (1) {
        uint8_t *s = UART_ReceiveString();
        if (s) {
            // got a full string terminated by \n or \r
            if (strcmp((char*)s, "Hello from arduino") == 0) {
                // blink LED once
                Port_SetPinChannelValue(PORT_D, HIGH, 7);
                _delay_ms(500);
                Port_SetPinChannelValue(PORT_D, LOW, 7);
                _delay_ms(500);
            }
        }
    }
}*/

/*------------------------------------------------------------------------------------------------------------------------*/

//UART string transmit

/*int main (void){

    UART_Init(UART_BAUD_9600);
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);

    while(1){
        UART_TransmitString("Hello world! \r \n");
        Port_SetPinChannelValue ( PORT_D , HIGH , 7);
        _delay_ms(2000);
        Port_SetPinChannelValue ( PORT_D , LOW , 7);
        _delay_ms(2000);

    }
}*/

/*--------------------------------------------------------------------------------------------*/

//SPI testing

//SPI transmit string
/*int main(void){
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);
    Port_SetPinChannelValue(PORT_D, LOW, 7);

    SPI_MasterInit(SPI_CLK_64);
    SPI_CFG(SPI_MODE_0, SPI_MSB);

    while (1) {
        SPI_MasterTransmitString((uint8_t*)"Hello from atmega");

        Port_SetPinChannelValue(PORT_D, HIGH, 7);
        _delay_ms(100);
        Port_SetPinChannelValue(PORT_D, LOW, 7);

        _delay_ms(1000);
    }
}*/

/*-----------------------------------------------------------------------------------------------------*/

//SPI receive string

/*int main(void) {
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);
    Port_SetPinChannelValue(PORT_D, LOW, 7);

    SPI_SlaveInit();
    SPI_CFG(SPI_MODE_0, SPI_MSB);

    while (1) {
        uint8_t *msg = SPI_ReceiveString();
        if (msg) {
            if (strcmp((char*)msg, "Hello from arduino") == 0) {
                // Blink LED
                Port_SetPinChannelValue(PORT_D, HIGH, 7);
                _delay_ms(500);
                Port_SetPinChannelValue(PORT_D, LOW, 7);
                _delay_ms(500);
            }
        }
    }
}*/
