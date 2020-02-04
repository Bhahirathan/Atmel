/*
 * buzzz.c
 *
 * Created: 18-10-2019 15:19:34
 * Author : Bhahirathan
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA =(1<<7);
    /* Replace with your application code */
    while (1) 
    {
		PORTA = (1<<7);
		_delay_ms(1000);
		PORTA = (0<<7);
		_delay_ms(1000);
    }
}

