#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
uint8_t cnt = 0;
uint8_t state = 0;
uint8_t stateBuff;
bool isRun = true;
bool tog = false;
#define CMP_T 23437
// 23437
ISR(INT0_vect)
{
    // save clock and tcnt
    uint16_t tmp = TCNT1;
    uint16_t tmp1 = TCCR1B;
    // open clock
    TCNT1 = 0;
    TCCR1B |= 0x05;
    while (!(PIND & (1 << PIND2)));
    if (TCNT1 > CMP_T)
    {
        tog = !tog;
        if (tog)
        {
            state = 3;
            tmp1 &= ~(0x05);
        }
        else
        {
            if (!isRun)
            {
                tmp1 ^= 0x05;
                state = stateBuff;
                isRun = true;
            }
        }
    }
    // close clock
    TCCR1B &= ~(0x05);
    // load clock and tcnt
    TCNT1 = tmp;
    TCCR1B = tmp1;
    // if not 3 sec op toggle clock
    if (!tog)
    {
        TCCR1B ^= 0x05;
        if (!(TCCR1B & 0x05))
        {
            isRun = false;
            stateBuff = state;
        }
        else
        {
            isRun = true;
        }
    }

    while (!(PIND & (1 << PIND2)));
}
ISR(TIMER1_OVF_vect)
{
    cnt += 1;
    state = cnt % 3;
    TCNT1 = 65536UL - 7812UL;
}
void init(){
    // led pc 0-2
    DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);
    // pull up switch PD2
    PORTD |= (1 << PD2);

    TCCR1B |= 0x05;
    TIMSK1 |= (1 << TOIE1);
    TCNT1 = 65536UL - 7812UL;

    EIMSK |= 0x01;
    EICRA |= 0x02;
    sei();
}
int main()
{
    init();
    while (1)
    {

        switch (state)
        {
        case 0:
            PORTC |= (1 << PC0);
            PORTC &= ~(1 << PC1);
            PORTC &= ~(1 << PC2);
            break;
        case 1:
            PORTC |= (1 << PC1);
            PORTC &= ~(1 << PC0);
            PORTC &= ~(1 << PC2);
            break;
        case 2:
            PORTC |= (1 << PC2);
            PORTC &= ~(1 << PC1);
            PORTC &= ~(1 << PC0);
            break;
        default:
            PORTC &= ~(1 << PC0);
            PORTC &= ~(1 << PC1);
            PORTC &= ~(1 << PC2);
            break;
        }
    }
}