#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
void main()
{
    DDRB |= 0x02;
    while(1){
        PORTB |= 0x02;
        _delay_ms(1000);
        PORTB &= ~(0x02);
        _delay_ms(1000);
    }
  
}