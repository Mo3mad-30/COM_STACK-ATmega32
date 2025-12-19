#include "Timer.h"
#include <stdint.h>

#define F_CPU 8000000UL 

static inline void sei_asm(void){
    __asm__ __volatile__ ("sei" ::: "memory");
}

static inline void cli_asm(void){
    __asm__ __volatile__ ("cli" ::: "memory");
}

//helper function to write to OCR1A register

static inline void write_OCR1A(uint16_t value){
    OCR1AH = (uint8_t)(value >> 8);
    OCR1AL = (uint8_t)(value & 0xFF);
}

uint8_t Set_Prescaler(Timer_Prescaler ps) {

    //clear cs bits first
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

    switch (ps)
    {
    case Timer_PS_1:
        TCCR1B |= (1 << CS10);
        break;
    case Timer_PS_8:
        TCCR1B |= (1 << CS11);
        break;
    case Timer_PS_64:
        TCCR1B |= (1 <<CS11) | (1 << CS10);
        break;
    case Timer_PS_256:
        TCCR1B |= (1 << CS12);
        break;
    case Timer_PS_1024:
        TCCR1B |=( 1 << CS12) | ( 1 << CS10);
        break;
    default: 
        return 1; //invalid prescaler
        }

        return 0; //valid prescaler

}

void Timer_delay_ms(uint32_t delay_ms) {
    //1) compute total ticks
    uint64_t Total_ticks = ((uint64_t)F_CPU * (uint64_t)delay_ms ) / 1000UL;
    uint32_t Ticks_needed;
    Timer_Prescaler selected_prescaler;

    //2)find suitable prescaler
    selected_prescaler = Timer_PS_1;
    Ticks_needed = (uint32_t)(Total_ticks / selected_prescaler);
    if (Ticks_needed <= 65535) {
        selected_prescaler = Timer_PS_1;
    }
    else {
        Ticks_needed = (uint32_t)(Total_ticks / Timer_PS_8);
        if (Ticks_needed <= 65535) {
            selected_prescaler = Timer_PS_8;
        }
        else {
            Ticks_needed = (uint32_t)(Total_ticks / Timer_PS_64);
            if (Ticks_needed <= 65535) {
                selected_prescaler = Timer_PS_64;
            }
            else {
                Ticks_needed = (uint32_t)(Total_ticks / Timer_PS_256);
                if (Ticks_needed <= 65535) {
                    selected_prescaler = Timer_PS_256;
                }
                else {
                    Ticks_needed = (uint32_t)(Total_ticks / Timer_PS_1024);
                    selected_prescaler = Timer_PS_1024;
                }
            }
        }
    }

    //3)compute OCR1A value
    uint16_t value = Ticks_needed - 1;

    //4) save current register states
    uint8_t save_TCCR1A = TCCR1A;
    uint8_t save_TCCR1B = TCCR1B;
    uint8_t save_TIMSK = TIMSK;

    //5) clear waveform bits and other relevant bits 
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); 
    TCCR1A &= ~((1 << WGM10) | (1 << WGM11));             
    TCCR1B = (TCCR1B & ~(1 << WGM13)) | (1 << WGM12);     // (CTC mode)

    //6)reset counter
    TCNT1H = 0;
    TCNT1L = 0;

    //7)write OCR1A
    write_OCR1A(value);

    //8) clear compare flag (writing 1 clears)
    TIFR |= (1 << OCF1A);

    // start timer
    Set_Prescaler(selected_prescaler);

    // wait for match (interrupts still enabled here!)
    while (!(TIFR & (1 << OCF1A))) {
        // UART/SPI ISRs can run in background
    }

    // stop timer
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));

    //10) restore the saved states of the registers
    TCCR1A = save_TCCR1A;
    TCCR1B = save_TCCR1B;
    TIMSK  = save_TIMSK;
}
