/*
 * ultra.c
 *
 * Created: 23-12-2019 14:15:06
 * Author : Bhahirathan
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"

void main()
{
	int co=0;
	unsigned char r;
	adc_init();
	uart_init();

	while(1)
	{
		r=getdata(1);
		uart_num(r);
		uart_string("\n");
		_delay_ms(14000);
		if(r==128||r==127)
		{
			co++;
		}
		if(co==10)
		{
			co=0;
			uart_string("Out of Labour");
		}
	}
	
}
