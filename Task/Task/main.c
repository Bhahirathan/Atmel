/*
 * Task.c
 *
 * Created: 19-10-2019 15:32:51
 * Author : Bhahirathan
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "uart.h"


int main(void)
{
	int i,j;
	DDRB=0b11111111;
	DDRA =(1<<7);
		adc_init();
		uart_init();
    /* Replace with your application code */
    while (1) 
    {
		PORTB= 0b00011000;
		_delay_ms(1000);
		PORTB= 0b00100100; 
		_delay_ms(1000);
		PORTB= 0b01000010;
		_delay_ms(1000);
		PORTB= 0b10000001;
		_delay_ms(1000);
	
	}
}

