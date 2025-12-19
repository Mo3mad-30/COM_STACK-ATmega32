
#ifndef UART_H
#define UART_H
#include <stdint.h>
#include "Port.h"
#include "Port_cfg.h"

//In UART , data is sent byte by byte , according to a certain baud rate
//through a transmission line Tx and a Reception line Rx
// Data frame : start bit + * data bits + parity bit + stop bit

typedef enum{
    UART_BAUD_300 = 300,
    UART_BAUD_2400 = 2400,
    UART_BAUD_9600 = 9600,
    UART_BAUD_19200 = 19200,
    UART_BAUD_28800 = 28800
} UART_BAUD_RATE;

//typedef char uint8_t;

//UART registers base adresses
#define UDR_BASE_ADDRESS 0x2C
#define UBRRH_BASE_ADDRESS 0x40
#define UBRRL_BASE_ADDRESS 0x29
#define UCSRA_BASE_ADDRESS 0x2B
#define UCSRB_BASE_ADDRESS 0x2A
#define UCSRC_BASE_ADDRESS 0x40

//Status register 
#define SREG_BASE_ADDRESS 0x5F

//accessing SREG register
#define SREG (*(volatile uint8_t *)SREG_BASE_ADDRESS)

//accessing UART regissters
#define UDR (*(volatile uint8_t *)UDR_BASE_ADDRESS)
#define UBRRH  (*(volatile uint8_t *)UBRRH_BASE_ADDRESS)
#define UBRRL  (*(volatile uint8_t *)UBRRL_BASE_ADDRESS)
#define UCSRA (*(volatile uint8_t *)UCSRA_BASE_ADDRESS)
#define UCSRB  (*(volatile uint8_t *)UCSRB_BASE_ADDRESS)
#define UCSRC  (*(volatile uint8_t *)UCSRC_BASE_ADDRESS)

//SREG register bit
#define I 7

//SEI macro
//#define SEI() (SREG |= (1 << I))

//UART register bits

//UCSRA
#define RXC 7
#define TXC 6
#define UDRE 5

//UCSRB
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN 4
#define TXEN 3


//UCSRC
#define URSEL 7
//#define UMSEL 6 NOT NEEDED (only asynchronous mode used)
#define USBS 3
#define UCSZ1 2
#define UCSZ0 1





void UART_Init(UART_BAUD_RATE baud_rate);
//Initialize UART with the specified baud rate
void UART_Transmit(uint8_t data);
void UART_TransmitString(uint8_t* string);
//Transmit a byte or a string through UART
uint8_t UART_Receive(void);
uint8_t* UART_ReceiveString(void);
//Receive a byte or a string through UART
void __vector_13(void) __attribute__ ((signal, used)); //RXC_vect
void __vector_14(void) __attribute__ ((signal, used)); //UDRE_vect
void __vector_15(void) __attribute__ ((signal, used)); //TXC_vect
//Interrupt service routines for UART

#endif