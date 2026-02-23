#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
void main()
{
    DDRB |= 0x01;
    while(1){
        PORTB |= 0x01;
        _delay_ms(1000);
        PORTB &= ~(0x01);
        _delay_ms(1000);
    }
  
}