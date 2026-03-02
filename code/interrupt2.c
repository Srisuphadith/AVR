#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t mask = 0x01;
ISR(INT0_vect){
    mask ^= 0x01;
    PORTD &= ~1;
    // if ((PIND & (1<<2)) == 0){
    //     _delay_ms(50);
    //     if ((PIND & (1<<2)) == 0){
    //         mask ^= 1;
    //         while((PIND & (1<<2)) == 0);
    //     }
    // }
}
int main(){
    EIMSK |= 0x01;
    EICRA |= 0x02;
    sei();

    PORTD |= (1 << PD2);
    DDRB |= 0x01;
    //PORTB = 0x01;
    while(1){
        if(mask){
            PORTB |= 1 ;
             for(int i=0; i<100; i++){
                _delay_ms(10);
             }
            
            // PORTB &= ~1 ;
            // _delay_ms(2000);
        }else{
            PORTB &= ~1;
        }
    }
}