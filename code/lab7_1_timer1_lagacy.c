#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t mask = 0x01;
ISR(INT0_vect){
    mask ^= 0x01;
    if(mask){
        PORTB |= 0x01;
    }else{
        PORTB &= ~(0x01);
    }
    _delay_ms(100);
    while(!(PIND & (1 << PIND2)));
    TCCR1B ^= 0x05;
    TCNT1 = 65536UL - 15625UL;
}
ISR(TIMER1_OVF_vect){
    PORTB = (PORTB^0x01) & mask;
    TCNT1 = 65536UL - 15625UL;
}
int main(){
    EIMSK |= 0x01;
    EICRA |= 0x02;

    TCCR1B |= 0x05;
    TIMSK1 |= (1 << TOIE1);
    TCNT1 = 65536UL - 15625UL;
    sei();

    PORTD |= (1 << PD2);
    DDRB |= 0x01;

    while(1){
    
    }
}