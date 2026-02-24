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
        // Normal is 1 if press will be 0
        // (0(touch) AND 1 ) == 0
        while ((PIND & 0x01) && (PIND & 0x02))
        {
            _delay_ms(50);
        }

        PORTB ^= 0x02; // ON-OFF LED

        // ~(0(touch) AND 1 ) == ~0 == 1
        while (!((PIND & 0x01) && (PIND & 0x02)))
        {
            _delay_ms(50);
        }
    }
}