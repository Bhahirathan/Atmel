/*
 * COMM_Control.c
 *
 * Created: 18-10-2019 16:08:10
 * Author : Bhahirathan
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
	uart_init();
	PORTC=0xFF;
    while (1) 
    {
		char opt= uart_read();
		if(opt=='A')
		{
			PORTC=0xF0;	
			uart_string("Relay 1 is On\n");
		}
		if(opt=='B')
		{
			PORTC=0x0F;	
			uart_string("Relay 2 is On\n");
		}
		if(opt=='C')
		{
			PORTC=0x00;
			uart_string("Relay 1,2 is Off\n");
		}
		
		
    }
}

