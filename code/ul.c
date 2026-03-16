#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
//-------------LCD FUNCTION-------------
void pushData(){
 	PORTD |= 0x20;
  	_delay_ms(1);
  	PORTD &= ~(0x20);
    _delay_ms(1);
}
void sendData(uint8_t data,bool rs){
  if(rs){
  	PORTD |= 0x40;
  }
 	PORTD |= (data >> 4) & 0x0F; 
  	pushData();
  	PORTD &= ~(0x0F);
   	PORTD |= data & 0x0F; 
  	pushData();
  	PORTD &= ~(0x0F);
   if(rs){
  	PORTD &= ~(0x40);
  }
}
void lcdPrintString(char data[]){
  for(int i = 0;data[i] != '\0';i++){
    sendData(data[i],1);
  }
}
void lcdPrintChar(char data){
    sendData(data,1);
}
void lcdInit(){
  	sendData(0x33,0);
  	sendData(0x32,0);
  	sendData(0x28,0);
  	sendData(0x0E,0);
  	sendData(0x01,0);
}
void lcdHome(){
	sendData(0x80,0);
}
void lcdLine2(){
	sendData(0xC0,0);
}
void lcdClear(){
	sendData(0x01,0);
}
//-------------LCD FUNCTION-------------

volatile uint16_t startTrick, endTrick;
float duration;
float distance;
ISR(TIMER1_CAPT_vect)
{
    if (TCCR1B & (1 << ICES1))
    {
        startTrick = ICR1;
        //set neg edge
        TCCR1B &= ~(1 << ICES1);
    }
    else
    {
        endTrick = ICR1;
        //set rising edge
        TCCR1B |= (1 << ICES1);
        //cal duration by counting value multiple period
        duration = (endTrick-startTrick)/7812.0;
        // sound speed,distance and time relation 2s/t = 331+0.6T ,T=25
        // solved equation 17300*t cm
        distance = 17300*duration;
    }
}

int main()
{
    //--------for counting duration echo pin from ultrasonic--------
    // prescalar /1024
    TCCR1B |= 0x05;
    //Input Capture Interrupt Enable
    TIMSK1 |= (1 << ICIE1);
    //trigger interrupt at rising edge 
    TCCR1B |= (1 << ICES1);
    sei();


    //--------for send trigger to ultrasonic--------
    //OC2A for trigger pin at ultrasonic
    DDRB |= (1<<PB3);
    //set Fast PWM mode
    TCCR2A |= (1 << WGM20) | (1 << WGM21);
    //Clear OC2A on compare match, set OC2A at BOTTOM,(non-inverting mode).
    TCCR2A |= (1 << COM2A1);
    //set prescalar 256
    TCCR2B |= (1 << CS22) | (1 << CS21);
    //duty cycle 10 %
    OCR2A = (0.1) * 255;


    //--------LCD init pin--------
    DDRD |= 0x6F;
    lcdInit();

    while (1)
    {
        //print measure value
        char buff[20];
        itoa(distance,buff,10);
        lcdClear();
        lcdPrintString(buff);
        _delay_ms(100);
    }
}