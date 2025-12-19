#include "SPI.h"
#include "UART.h"
#include "Port.h"
#include "Port_cfg.h"
#include "Comm.h"

void Select_Protocol(UART_BAUD_RATE baud , SPI_CLOCK_RATE clk , SPI_MODE mode , SPI_DATA_ORDER dord);

uint8_t SEL_ReceiveByte (void);
uint8_t* SEL_ReceiveString(void);

void SEL_TransmitByte(uint8_t byte);
void SEL_TransmitString(uint8_t* string);