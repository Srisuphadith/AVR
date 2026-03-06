#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t mask = 0x01;
ISR(INT0_vect){
    mask ^= 0x01;
    PORTB ^= 0x01;
    _delay_ms(100);
    while(!(PIND & (1 << PIND2)));
}
int main(){
    EIMSK |= 0x01;
    EICRA |= 0x02;
    sei();

    PORTD |= (1 << PD2);
    DDRB |= 0x01;

    while(1){
        _delay_ms(2000);
        PORTB = (PORTB^0x01) & mask;
    }
}