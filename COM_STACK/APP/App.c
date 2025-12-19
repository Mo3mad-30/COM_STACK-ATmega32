#include "UART.h"
#include "SPI.h"
#include "Comm.h"
#include "Selector.h"
#include "Port.h"
#include "Timer.h"
#include <stdint.h>
//#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#define Car_speed 170
#define Distance 15

/*int main (void){
    Select_Protocol(UART_BAUD_9600 , SPI_CLK_16 , SPI_MODE_0 , SPI_MSB);

    Port_SetPinDirection(PORT_D , OUTPUT , 7);

    Timer_delay_ms(6000);
    Timer_delay_ms(3000);

    Port_SetPinChannelValue ( PORT_D , HIGH , 7);
    Timer_delay_ms(1000);
    Port_SetPinChannelValue (PORT_D , LOW , 7);
    Timer_delay_ms(1000);

    char tmp[8];

    SEL_TransmitString("Current car speed =\n");
    Timer_delay_ms(1000);
    sprintf(tmp, "%u", (unsigned)Car_speed);
    SEL_TransmitString((uint8_t*)tmp);
    Timer_delay_ms(1000);

    SEL_TransmitString("Distance till next obstacle =\n");
    Timer_delay_ms(1000);
    sprintf(tmp, "%u", (unsigned)Distance);
    SEL_TransmitString((uint8_t*)tmp);
    Timer_delay_ms(1000);

    Port_SetPinChannelValue ( PORT_D , HIGH , 7);
    Timer_delay_ms(1000);
    Port_SetPinChannelValue (PORT_D , LOW , 7);
    Timer_delay_ms(1000);

    // >>> ADD: clock one byte so the slave's replyByte is shifted out
    SPI_MasterTransmit(0x00);        // dummy write -> clocks in replyByte from Arduino
    Timer_delay_ms(2);               // tiny settle to let ISR run

    uint8_t new_speed = SEL_ReceiveByte();   // now contains 40 or 120
    Timer_delay_ms(1000);

    SEL_TransmitString("New car speed =\n");
    Timer_delay_ms(1000);
    sprintf(tmp, "%u", (unsigned)new_speed);
    SEL_TransmitString((uint8_t*)tmp);

    while(1);
}*/


/*int main (void){
    Select_Protocol(UART_BAUD_9600 , SPI_CLK_16 , SPI_MODE_0 , SPI_MSB);

    Port_SetPinDirection(PORT_D , OUTPUT , 7);

        Timer_delay_ms(6000);
        Timer_delay_ms(3000);

        Port_SetPinChannelValue ( PORT_D , HIGH , 7);
        Timer_delay_ms(1000);
        Port_SetPinChannelValue (PORT_D , LOW , 7);
        Timer_delay_ms(1000);

        char tmp[8];

        SEL_TransmitString("Current car speed =\n");
        Timer_delay_ms(1000);
        SEL_TransmitByte(Car_speed);
       

        Timer_delay_ms(1000);

        SEL_TransmitString("Distance till next obstacle =\n");
        Timer_delay_ms(1000);
        SEL_TransmitByte(Distance);
        

        Port_SetPinChannelValue ( PORT_D , HIGH , 7);
        Timer_delay_ms(1000);
        Port_SetPinChannelValue (PORT_D , LOW , 7);
        Timer_delay_ms(1000);

        uint8_t new_speed = SEL_ReceiveByte();
        Timer_delay_ms(1000);

        SEL_TransmitString("New car speed =\n");
        Timer_delay_ms(1000);
        SEL_TransmitByte(new_speed);

        while(1);
}*/

/*int main(void){
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);

    while(1){
     Port_SetPinChannelValue(PORT_D, HIGH, 7); 
            Timer_delay_ms(500);
    Port_SetPinChannelValue(PORT_D, LOW, 7);  
            Timer_delay_ms(500);
    }
}*/

/*int main(void) {
    Select_Protocol(UART_BAUD_9600, SPI_CLK_16, SPI_MODE_0, SPI_MSB);
    Port_SetPinDirection(PORT_D, OUTPUT, 7);
    while(1){
    Port_SetPinChannelValue(PORT_D, HIGH, 7); // LED ON before flush

    // Actually transmit something
    UART_Transmit('A');

    Timer_delay_ms(500);

    Port_SetPinChannelValue(PORT_D, LOW, 7);  // LED OFF after flush
    }
}*/

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

/*int main(void) {
    UART_Init(UART_BAUD_9600);
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);



    while (1) {
        UART_Transmit('A');  
        Port_SetPinChannelValue(PORT_D, HIGH, 7); 
        Timer_delay_ms(1000);
        Port_SetPinChannelValue(PORT_D, LOW, 7);
        Timer_delay_ms(1000);
    }
}*/

/*int main (void){

    UART_Init(UART_BAUD_9600);
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);

    while(1){
        UART_TransmitString("Hello world! \r \n");
        Port_SetPinChannelValue ( PORT_D , HIGH , 7);
        Timer_delay_ms(500);
        Port_SetPinChannelValue ( PORT_D , LOW , 7);
        Timer_delay_ms(500);

    }
}*/

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

/*int main (void){
    while(1);
}*/


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
                Timer_delay_ms(500);
                Port_SetPinChannelValue(PORT_D, LOW, 7);
                Timer_delay_ms(500);
            }
        }
    }
}


/*int main(void) {
    // Init ports and LED
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7); // PD7 LED
    Port_SetPinChannelValue(PORT_D, LOW, 7);

    // Configure SPI master (mode 0, MSB first), clock rate match Arduino defaults
    SPI_CFG(SPI_MODE_0, SPI_MSB);
    SPI_MasterInit(SPI_CLK_64);

    // small delay for stability
    Timer_delay_ms(100);

    while (1) {
        // 1) Send the string (includes '\0' terminator; your MCAL uses '\0')
        SPI_MasterTransmitString((uint8_t*)"Hello from atmega");

        // 2) Immediately check received string (blocking SPI ensured ISR finished)
        uint8_t *msg = SPI_ReceiveString();
        if (msg) {
            // if it equals what we sent, blink LED quickly
            if (strcmp((char*)msg, "Hello from atmega") == 0) {
                Port_SetPinChannelValue(PORT_D, HIGH, 7);
                Timer_delay_ms(200);
                Port_SetPinChannelValue(PORT_D, LOW, 7);
                Timer_delay_ms(200);
            }
        }

        // wait a bit before sending again
        Timer_delay_ms(1000);
    }

    return 0;
}*/



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
        Timer_delay_ms(100);
        Port_SetPinChannelValue(PORT_D, LOW, 7);

        Timer_delay_ms(1000);
    }
}*/

/*int main (void){
    Select_Protocol(UART_BAUD_9600 , SPI_CLK_16 , SPI_MODE_0 , SPI_MSB);

    Port_SetPinDirection(PORT_D , OUTPUT , 7);

    Timer_delay_ms(6000);
    Timer_delay_ms(3000);

    Port_SetPinChannelValue ( PORT_D , HIGH , 7);
    Timer_delay_ms(1000);
    Port_SetPinChannelValue (PORT_D , LOW , 7);
    Timer_delay_ms(1000);

    char tmp[8];

    SEL_TransmitString("Current car speed =\n");
    Timer_delay_ms(1000);
    sprintf(tmp, "%u", (unsigned)Car_speed);
    SEL_TransmitString((uint8_t*)tmp);
    Timer_delay_ms(1000);

    SEL_TransmitString("Distance till next obstacle =\n");
    Timer_delay_ms(1000);
    sprintf(tmp, "%u", (unsigned)Distance);
    SEL_TransmitString((uint8_t*)tmp);
    Timer_delay_ms(1000);

    Port_SetPinChannelValue ( PORT_D , HIGH , 7);
    Timer_delay_ms(1000);
    Port_SetPinChannelValue (PORT_D , LOW , 7);
    Timer_delay_ms(1000);

    // >>> ADD: clock one byte so the slave's replyByte is shifted out
    SPI_MasterTransmit(0x00);        // dummy write -> clocks in replyByte from Arduino
    Timer_delay_ms(2);               // tiny settle to let ISR run

    uint8_t new_speed = SEL_ReceiveByte();   // now contains 40 or 120
    Timer_delay_ms(1000);

    SEL_TransmitString("New car speed =\n");
    Timer_delay_ms(1000);
    sprintf(tmp, "%u", (unsigned)new_speed);
    SEL_TransmitString((uint8_t*)tmp);

    while(1);
}*/

/*int main (void){

    UART_Init(UART_BAUD_9600);
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);

    while(1){
        UART_TransmitString("Hello from ATmega! \r \n");
        Port_SetPinChannelValue ( PORT_D , HIGH , 7);
        Timer_delay_ms(1000);
        Port_SetPinChannelValue ( PORT_D , LOW , 7);
        Timer_delay_ms(1000);

    }
}*/

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
                Timer_delay_ms(500);
                Port_SetPinChannelValue(PORT_D, LOW, 7);
                Timer_delay_ms(500);
            }
        }
    }
}*/

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
                Timer_delay_ms(500);
                Port_SetPinChannelValue(PORT_D, LOW, 7);
                Timer_delay_ms(500);
            }
        }
    }
}*/

int main(void){
    Port_Init();
    Port_SetPinDirection(PORT_D, OUTPUT, 7);
    Port_SetPinChannelValue(PORT_D, LOW, 7);

    SPI_MasterInit(SPI_CLK_64);
    SPI_CFG(SPI_MODE_0, SPI_MSB);

    while (1) {
        SPI_MasterTransmitString((uint8_t*)"Hello from atmega");

        Port_SetPinChannelValue(PORT_D, HIGH, 7);
        Timer_delay_ms(100);
        Port_SetPinChannelValue(PORT_D, LOW, 7);

        Timer_delay_ms(1000);
    }
}