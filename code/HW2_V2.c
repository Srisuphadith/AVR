// define CPU frequence internal RC Oscillator 8 MHz = 8,000,000 Hz
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void main()
{
    // Input pull-up
    PORTD |= 0x03;
    // Output LED
    DDRB |= 0x02;
    while (1)
    {
        _delay_ms(50);
        if(!(PIND & 0x01)){
            PORTB ^= 0x02;
        }
        while(!(PIND & 0x01));
        _delay_ms(50);
        if(!(PIND & 0x02)){
            PORTB ^= 0x02;
        }
        while(!(PIND & 0x02));
    }
}