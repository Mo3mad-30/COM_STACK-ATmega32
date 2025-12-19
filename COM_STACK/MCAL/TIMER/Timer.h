#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define TCCR1A_BASE_ADDRESS 0x4F
#define TCCR1B_BASE_ADDRESS 0x4E
#define OCR1AL_BASE_ADDRESS 0x4A
#define OCR1AH_BASE_ADDRESS 0x4B
#define TIFR_BASE_ADDRESS 0x58
#define TIMSK_BASE_ADDRESS 0x59
#define TCNT1L_BASE_ADDRESS 0x4C
#define TCNT1H_BASE_ADDRESS 0x4D

#define TCCR1A (*(volatile uint8_t *)TCCR1A_BASE_ADDRESS)
#define TCCR1B  (*(volatile uint8_t *)TCCR1B_BASE_ADDRESS)
#define OCR1AL  (*(volatile uint8_t *)OCR1AL_BASE_ADDRESS)
#define OCR1AH (*(volatile uint8_t *)OCR1AH_BASE_ADDRESS)
#define TIFR  (*(volatile uint8_t *)TIFR_BASE_ADDRESS)
#define TIMSK  (*(volatile uint8_t *)TIMSK_BASE_ADDRESS)
#define TCNT1L (*(volatile uint8_t *)TCNT1L_BASE_ADDRESS)
#define TCNT1H  (*(volatile uint8_t *)TCNT1H_BASE_ADDRESS)

#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4

#define CS10 0
#define CS11 1
#define CS12 2

#define OCF1A 4

typedef enum{
    Timer_PS_1 = 1UL,
    Timer_PS_8 = 8UL,
    Timer_PS_64 = 64UL,
    Timer_PS_256 = 256UL,
    Timer_PS_1024 = 1024UL
} Timer_Prescaler;

uint8_t Set_Prescaler (Timer_Prescaler ps);

void Timer_delay_ms(uint32_t delay_ms);
#endif