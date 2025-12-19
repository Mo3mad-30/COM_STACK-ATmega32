//functions definitions , port adresses , names and directions

#include <stdint.h> 
#include "Port_cfg.h"
#ifndef PORT_H
#define PORT_H


//Enums for ports amd their properities

typedef enum{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D
} Port_Name;

typedef enum {
    INPUT = 0,
    OUTPUT = 1
} Port_Direction;

typedef enum {
    LOW = 0,
    HIGH = 1
} Port_Value;

//typedef char uint8_t; ;

//base adresses 

//PORT A
#define PORTA_BASE_ADDRESS 0x3B
#define DDRA_BASE_ADDRESS 0x3A
#define PINA_BASE_ADDRESS 0x39
//PORT B
#define PORTB_BASE_ADDRESS 0x38
#define DDRB_BASE_ADDRESS 0x37
#define PINB_BASE_ADDRESS 0x36
//PORT C
#define PORTC_BASE_ADDRESS 0x35
#define DDRC_BASE_ADDRESS 0x34  
#define PINC_BASE_ADDRESS 0x33
//PORT D
#define PORTD_BASE_ADDRESS 0x32
#define DDRD_BASE_ADDRESS 0x31
#define PIND_BASE_ADDRESS 0x30


//Macros for accessing port registers
#define PORTA (*(volatile uint8_t *)PORTA_BASE_ADDRESS)
#define DDRA  (*(volatile uint8_t *)DDRA_BASE_ADDRESS)
#define PINA  (*(volatile uint8_t *)PINA_BASE_ADDRESS)

#define PORTB (*(volatile uint8_t *)PORTB_BASE_ADDRESS)
#define DDRB (*(volatile uint8_t *)DDRB_BASE_ADDRESS)
#define PINB (*(volatile uint8_t *)PINB_BASE_ADDRESS)

#define PORTC (*(volatile uint8_t *)PORTC_BASE_ADDRESS)
#define DDRC (*(volatile uint8_t *)DDRC_BASE_ADDRESS)
#define PINC (*(volatile uint8_t *)PINC_BASE_ADDRESS)

#define PORTD (*(volatile uint8_t *)PORTD_BASE_ADDRESS)
#define DDRD (*(volatile uint8_t *)DDRD_BASE_ADDRESS)
#define PIND (*(volatile uint8_t *)PIND_BASE_ADDRESS)   


void Port_Init(void);
    // Initialization code for the port

void Port_SetPinDirection (Port_Name port , Port_Direction direction , uint8_t pin);
    // Set the direction of the specified pin

void Port_SetPinChannelValue (Port_Name port  , Port_Value value , uint8_t pin);
    // Set the value of the specified channel

void Port_SetPortDirection (Port_Name port , Port_Direction direction );
    // Set the direction of the entire port

void Port_SetPortChannelValue (Port_Name port , Port_Value value );
    // Set the value of the entire port

#endif 