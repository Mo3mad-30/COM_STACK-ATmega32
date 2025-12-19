//functions implementations
#define F_CPU 8000000UL  

#include "Port.h"
#include <util/delay.h>
#include <stdint.h>
#include "Port_cfg.h"

//helper functions
volatile uint8_t* getPortOutputRegister(Port_Name port) {
    switch (port) {
        case PORT_A: return (volatile uint8_t *)PORTA_BASE_ADDRESS;
        case PORT_B: return (volatile uint8_t *)PORTB_BASE_ADDRESS;
        case PORT_C: return (volatile uint8_t *)PORTC_BASE_ADDRESS;
        case PORT_D: return (volatile uint8_t *)PORTD_BASE_ADDRESS;
    }
}

volatile uint8_t* getPortDirectionRegister(Port_Name port) {
    switch (port) {
        case PORT_A: return (volatile uint8_t *)DDRA_BASE_ADDRESS;
        case PORT_B: return (volatile uint8_t *)DDRB_BASE_ADDRESS;
        case PORT_C: return (volatile uint8_t *)DDRC_BASE_ADDRESS;
        case PORT_D: return (volatile uint8_t *)DDRD_BASE_ADDRESS;
}
}

volatile uint8_t* getPortInputRegister(Port_Name port) {
    switch (port) {
        case PORT_A: return (volatile uint8_t *)PINA_BASE_ADDRESS;
        case PORT_B: return (volatile uint8_t *)PINB_BASE_ADDRESS;
        case PORT_C: return (volatile uint8_t *)PINC_BASE_ADDRESS;
        case PORT_D: return (volatile uint8_t *)PIND_BASE_ADDRESS;
    }
}

//initalization function from Port_cfg.h
void Port_Init(void) {
    //get configurations from Port_cfg.h
    
    getPortDirectionRegister(PORT_A);
    getPortOutputRegister(PORT_A);
    getPortInputRegister(PORT_A);
    Port_SetPortDirection(PORT_A, PORT_A_DIRECTION);
    Port_SetPortChannelValue(PORT_A, PORT_A_VALUE);

    getPortDirectionRegister(PORT_B);
    getPortOutputRegister(PORT_B);
    getPortInputRegister(PORT_B);
    Port_SetPortDirection(PORT_B, PORT_B_DIRECTION);
    Port_SetPortChannelValue(PORT_B, PORT_B_VALUE);

    getPortDirectionRegister(PORT_C);
    getPortOutputRegister(PORT_C);  
    getPortInputRegister(PORT_C);
    Port_SetPortDirection(PORT_C, PORT_C_DIRECTION);
    Port_SetPortChannelValue(PORT_C, PORT_C_VALUE);

    getPortDirectionRegister(PORT_D);
    getPortOutputRegister(PORT_D);
    getPortInputRegister(PORT_D);
    Port_SetPortDirection(PORT_D, PORT_D_DIRECTION);
    Port_SetPortChannelValue(PORT_D, PORT_D_VALUE);

}


//setting specific pin direction
void Port_SetPinDirection (Port_Name port , Port_Direction direction , uint8_t pin){
    switch (port){
        case PORT_A:
            if (direction == OUTPUT){
                DDRA |= (1 << pin);
            }
            else if(direction == INPUT){
                DDRA &= ~(1 << pin);
            }

             case PORT_B:
            if (direction == OUTPUT){
                DDRB |= (1 << pin);
            }
            else if(direction == INPUT){
                DDRB &= ~(1 << pin);
            }

             case PORT_C:
            if (direction == OUTPUT){
                DDRC |= (1 << pin);
            }
            else if(direction == INPUT){
                DDRC &= ~(1 << pin);
            }

             case PORT_D:
            if (direction == OUTPUT){
                DDRD |= (1 << pin);
            }
            else if(direction == INPUT){
                DDRD &= ~(1 << pin);
            }
    }
}

void Port_SetPinChannelValue (Port_Name port  , Port_Value value , uint8_t pin){

     switch (port){
        case PORT_A:
            if (value == HIGH){
                PORTA |= (1 << pin);
            }
            else if(value == LOW){
                PORTA &= ~(1 << pin);
            }

             case PORT_B:
            if (value == HIGH){
                PORTB |= (1 << pin);
            }
            else if(value == LOW){
                PORTB &= ~(1 << pin);
            }

             case PORT_C:
            if (value == HIGH){
                PORTC |= (1 << pin);
            }
            else if(value == LOW){
                PORTC &= ~(1 << pin);
            }

             case PORT_D:
            if (value == HIGH){
                PORTD |= (1 << pin);
            }
            else if(value == LOW){
                PORTD &= ~(1 << pin);
            }
    }

}


//setting whole port direction
void Port_SetPortDirection (Port_Name port , Port_Direction direction ){
    switch (port){
        case PORT_A:
            if (direction == OUTPUT){
                DDRA = 0xFF;
            }
            else if(direction == INPUT){
                DDRA = 0X00;
            }

             case PORT_B:
            if (direction == OUTPUT){
                DDRB = 0xFF;
            }
            else if(direction == INPUT){
                DDRB = 0X00;
            }

             case PORT_C:
            if (direction == OUTPUT){
                DDRC = 0xFF;
            }
            else if(direction == INPUT){
                DDRC = 0X00;
            }

             case PORT_D:
            if (direction == OUTPUT){
                DDRD = 0xFF;
            }
            else if(direction == INPUT){
                DDRD = 0X00;
            }
    }
    
}

void Port_SetPortChannelValue (Port_Name port , Port_Value value ){
    switch (port){
        case PORT_A:
            if (value == HIGH){
                PORTA =0xFF;
            }
            else if(value == LOW){
                PORTA = 0x00;
            }

             case PORT_B:
            if (value == HIGH){
                PORTB = 0xFF;
            }
            else if(value == LOW){
                PORTB = 0x00;
            }

             case PORT_C:
            if (value == HIGH){
                PORTC = 0xFF;
            }
            else if(value == LOW){
                PORTC = 0x00;
            }

             case PORT_D:
            if (value == HIGH){
                PORTD = 0xFF;
            }
            else if(value == LOW){
                PORTD = 0x00;
            }
    }

}

/*int main(void) {
//initialize the ports
    Port_Init();
// Set PD7 as outpuT
    Port_SetPinDirection(PORT_D, OUTPUT, 7);
    
    while (1) {
        // Turn LED ON
        Port_SetPinChannelValue(PORT_D, HIGH, 7);
        _delay_ms(200);

        // Turn LED OFF
        Port_SetPinChannelValue(PORT_D, LOW, 7);
        _delay_ms(2000);
    }
}*/