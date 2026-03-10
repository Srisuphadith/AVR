#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t is_active = 1; 

void setup() {
    DDRB |= (1 << PB5);
    
    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2);

    EICRA |= (1 << ISC01); 
    EIMSK |= (1 << INT0);  
    sei(); 
}

ISR(INT0_vect) {
    is_active = !is_active; 
    if (!is_active) {
        PORTB &= ~(1 << PB5);
    }else{
        PORTB |= (1 << PB5);
    }
    _delay_ms(70);
    while(!(PIND & (1 << PD2)));
}

int main(void) {
    setup();
    while (1) {
        if (is_active) {
            PORTB |= (1 << PB5);
            for(int i=0; i<200 && is_active; i++) _delay_ms(10); 
            
            PORTB &= ~(1 << PB5);
            for(int i=0; i<200 && is_active; i++) _delay_ms(10);
        }
    }
}