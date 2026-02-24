#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_ADDR 0x27
#define BL 0x08
#define EN 0x04
#define RW 0x02
#define RS 0x01

void TWI_Init()
{
    TWBR = 32;
    TWSR = 0x00;
    TWCR = (1 << TWEN);
}
void TWI_Start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}
void TWI_Write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}
void TWI_Stop()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
void lcdSendCMD(uint8_t data)
{
    TWI_Start();
    TWI_Write((LCD_ADDR << 1));
    TWI_Write((data & 0xF0) | EN | BL);
    TWI_Write((data & 0xF0) | BL);
    TWI_Write(((data << 4) & 0xF0) | EN | BL);
    TWI_Write(((data << 4) & 0xF0) | BL);
    TWI_Stop();
}

void lcdSendChar(unsigned char data)
{
    TWI_Start();
    TWI_Write((LCD_ADDR << 1));
    TWI_Write((data & 0xF0) | EN | BL | RS);
    TWI_Write((data & 0xF0) | BL | RS);
    TWI_Write(((data << 4) & 0xF0) | EN | BL | RS);
    TWI_Write(((data << 4) & 0xF0) | BL | RS);
    TWI_Stop();
}
void lcdSendString(char arr[])
{
    for (int i = 0; arr[i] != '\0'; i++)
    {
        lcdSendChar(arr[i]);
    }
}
void lcdHome()
{
    lcdSendCMD(0x80);
}
void lcdLine2()
{
    lcdSendCMD(0xC0);
}
void lcdClear()
{
    lcdSendCMD(0x01);
}
int main()
{
    TWI_Init();

    lcdSendCMD(0x33);
    lcdSendCMD(0x32);
    lcdSendCMD(0x28);
    lcdSendCMD(0x0E);
    lcdSendCMD(0x01);
    _delay_ms(20);
    lcdSendString("Hello world!");
    lcdLine2();
    lcdSendString("Hiura Mihate");
    while (1)
    {
    }
}