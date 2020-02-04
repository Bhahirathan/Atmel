/*
 * IOTC.c
 *
 * Created: 18-10-2019 13:05:21
 * Author : Bhahirathan
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{    
	DDRB=0b11111111;
    while (1) 
    {
		PORTB= 0xF0;
		_delay_ms(1500);
		PORTB = 0x0F;
		_delay_ms(1000);
    }
}

