/*
 * LED_BUZZ.c
 *
 * Created: 18-10-2019 15:32:22
 * Author : Bhahirathan
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRB=0b11111111;
	DDRA =(1<<7);
    while (1) 
    {
		PORTA = (1<<7);
		PORTB= 0xF0;
		_delay_ms(500);
		PORTB = 0x0F;
		PORTA = (0<<7);
		_delay_ms(50);
    }
}

