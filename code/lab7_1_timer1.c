#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Define CPU frequency
#define F_CPU 8000000UL

uint8_t mask = 0x01; // Mask to control LED state, initially set to turn on LED when INT0 is triggered
ISR(INT0_vect)
{
    mask ^= 0x01; // Toggle mask to change LED state on each button press
    if (mask)
    {
        PORTB |= 0x01; // |= (1 << PB0); // Turn on LED
    }
    else
    {
        PORTB &= ~0x01; // &= ~(1 << PB0); // Turn off LED
    }
    while (!(PIND & (1 << PD2)))
        ;                                // Wait for button release (PD2 is the pin for INT0)
    TCCR1B |= (1 << CS12) | (1 << CS10); // TCCR1B |= 0x05; // Start Timer1 with prescaler 1024
    TCNT1 = 65536UL - 15625UL;           // Set Timer1 to overflow after 2 seconds
}

ISR(TIMER_OVF_vect)
{
    PORTB = (PORTB ^ 0x01) & mask; // Toggle LED if mask is set
    TCNT1 = 65536UL - 15625UL;
    // delay for 2 seconds with 1024 prescaler
    //(8MHz / 1024 = 7812.5 counts per second, so 15625 counts for 2 seconds)
}

int main(void)
{
    DDRB |= 0x01;   // DDRB |= (1 << PB0); // Set PB0 as output
    PORTB &= ~0x01; // PORTB &= ~(1 << PB0); // Ensure LED is off

    EICRA |= (1 << ISC00); // EICRA |= 0x01; // Trigger INT0 on any logical change from the button
    EIMSK |= (1 << INT0);  // EIMSK |= 0x01; // Enable INT0

    TCCR1B |= (1 << CS12) | (1 << CS10); // TCCR1B |= 0x05; // Start Timer1 with prescaler 1024
    TCNT1 = 65536UL - 15625UL;           // Set Timer1 to overflow after 2 seconds
    TIMSK1 |= (1 << TOIE1);              // TIMSK1 |= 0x01; // Enable Timer1 overflow interrupt

    sei(); // Enable global interrupts

    while (1)
    {
        // Main loop does nothing, all work is done in ISRs
    }
}