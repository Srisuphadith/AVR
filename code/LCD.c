#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

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
int main(){
    DDRD |= 0x6F;
    lcdInit();
    lcdPrintString("Hello world");
    while (1)
    {
     
    }
    

    
}