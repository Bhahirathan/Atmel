/*
 * pir.c
 *
 * Created: 25-12-2019 19:17:46
 * Author : Bhahirathan
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "uart.h"
#define LED_OUTPUT	PORTB
#define PIR_Input	PINC

int main(void)
{
	DDRC = 0x00;	/* Set the PIR port as input port */
	DDRB = 0xff;
	adc_init();
	uart_init();
	unsigned char val;
    /* Replace with your application code */
    while (1) 
    {
		LED_OUTPUT = PIR_Input;
		val=getdata(1);
		uart_num(val);
		uart_string("\n");
		_delay_ms(11000);
    }
}

