#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void main()
{
    PORTD |= 0x03;
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