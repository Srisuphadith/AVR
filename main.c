#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
ISR(INT0_vect){
    //Toggle LED at PD3
	PORTD = (PORTD & ~0x08) | ((~PIND) & 0x08);
}
void main()
{
  //output led PD2
  DDRD |= 0x08;
  //Input pull-up at PD2
  PORTD |= 0x04;
  //falling edge mode at INT0
  EICRA |= (1 << ISC01);
  //Open interrupt at INT0(PD3)
  EIMSK |= (1 << INT0);    
  //Open Global intterrupt
  sei();
  
}