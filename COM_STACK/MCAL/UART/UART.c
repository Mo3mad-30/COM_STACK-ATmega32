#define F_CPU 8000000UL  

#include "UART.h"
#include <stdint.h>
//#include <util/delay.h>
#include <stdbool.h>

//for string reception
#define RX_Max_len 64

volatile uint8_t RX_Buffer[RX_Max_len];
volatile uint8_t RX_Index = 0;
volatile bool RX_done_flag = false;

//for string transmission
#define TX_Max_len 64

volatile uint8_t TX_Buffer [TX_Max_len];
volatile uint8_t TX_Index = 0;
volatile uint8_t TX_string_length = 0;
volatile bool TX_done_flag = false;


static inline void sei_asm(void){
    __asm__ __volatile__ ("sei" ::: "memory");
}

void UART_Init(UART_BAUD_RATE baud_rate){
    //set baud rate
    uint16_t ubrr = ( F_CPU / (16UL * baud_rate )) - 1;
    //set the baud rate registers
    UBRRH = (ubrr >> 8);
    UBRRL = ubrr;

    //clear the TXC in case it was set from previous transmissions
    UCSRA |= (1 << TXC);

    //set them off until we need them
    UCSRB &= ~(1 << TXCIE); 
    UCSRB &= ~(1 << UDRIE);   

    //enable TXEN and RXEN
    UCSRB |= (1 << TXEN) | (1 << RXEN) | (1<< RXCIE); /* | (1 << TXCIE) |(1 << UDRIE);*/

    //set frame format with UCSRC
    //set USEL to 1 to access UCSRC , UCSZ1 and UCSZ0 to 1 for 8 bit data , USBS default is zero for 1 stop bit
    UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

    //enable global interrupts
    sei_asm();
}


/*void UART_FlushTx(void) {
    // Clear TXC before starting
    UCSRA |= (1 << TXC);

    // Wait until TXC is set (means byte fully shifted out)
    while (!(UCSRA & (1 << TXC))) {
        // wait
    }
    // Clear again for safety
    UCSRA |= (1 << TXC);
}*/


/*void UART_FlushRx(void) {
    uint8_t dummy;
    while (UCSRA & (1 << RXC)) {
        dummy = UDR; // discard unread data
    }
}*/


//receive with interrupts
volatile uint8_t received_data;

void __vector_13(void){

    received_data = UDR;

    if (!RX_done_flag){
        if ( received_data == '\n' || received_data == '\r' || RX_Index >= RX_Max_len-1 ){
            RX_Buffer[RX_Index] = '\0'; //null terminator to indicate the end of the buffer
            RX_done_flag = true;
            RX_Index = 0 ; //reset for next process
        }
        else{
            RX_Buffer[RX_Index++] = received_data;
        }

    }

}

uint8_t UART_Receive(void){

  //  UART_FlushRx();

    return received_data;
}

uint8_t* UART_ReceiveString(void){

  //  UART_FlushRx();

    if(RX_done_flag == true){
        RX_done_flag = false;
        return (uint8_t*)RX_Buffer;
    }

    return (uint8_t*)0; 

}
volatile uint8_t transmited_data;

void __vector_14(void){

  
    if (TX_Index < TX_string_length){
        UDR = TX_Buffer[TX_Index++]; // write into the UDR
    }

    else { 
        UCSRB &= ~(1 << UDRIE); // disbale UDRIE interrupt
        TX_done_flag = true; //set the done flag
        TX_Index = 0; // reset teh index for the next transmission
    }
}


void __vector_15(void){

    UCSRA |= (1 << TXC); // clear TXC flag

    UCSRB &= ~(1 << TXCIE); // disable TXCIE interrupt
}


void UART_Transmit(uint8_t data){

    transmited_data = data;

    if (UCSRA & (1 << UDRE)){

        UDR = transmited_data; 

        UCSRB |= (1 << TXCIE);
    }

    else{

        UCSRB |= (1 << UDRIE);
    }

   // UART_FlushTx();

}



void UART_TransmitString(uint8_t* string){
    TX_string_length = 0; // reset the string length

    while (string[TX_string_length] != '\0' && TX_string_length < TX_Max_len - 1) {
        TX_Buffer[TX_string_length] = string[TX_string_length];
        TX_string_length++;
    }

    TX_Buffer[TX_string_length] = '\0'; // null terminator for the string

    TX_Index = 0; // reset the index for transmission
    TX_done_flag = false; // reset the done flag

    if (UCSRA & (1 << UDRE)) {
        UDR = TX_Buffer[TX_Index++]; // write into the UDR
        UCSRB |= (1 << UDRIE); // enable UDRIE interrupt
    } else {
        UCSRB |= (1 << UDRIE); // enable UDRIE interrupt
    }

    //UART_FlushTx();
}