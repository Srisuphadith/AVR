#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// PD6-> led
// PC5 -> potentiometer

ISR(ADC_vect){
    //set PWM duty cycle
    OCR0A = ((float)ADC/1024.0) * 255;
}
int main(){
    // 5v ref and ADC5
    ADMUX |= (1<<REFS0) | 0x05;
    //Enable, Start convertion, Enable interrupt, Free running, Prescalar 1024
    ADCSRA |= (1 << ADEN) |(1 << ADSC)| (1 << ADIE) | (1 << ADATE) | 0x07 ;

    //use OC0A
    DDRD |= (1<<PD6);
    //Fast PWM Mode
    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    //Clear OC0A on compare match, set OC0A at BOTTOM,(non-inverting mode).
    TCCR0A |= (1 << COM0A1);
    // prescalar /1
    TCCR0B |= (1 << CS00);
    sei();
    
    while (1)
    {

    }
    
}