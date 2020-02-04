/*
 * LDR.c
 *
 * Created: 19-10-2019 10:27:38
 * Author : Bhahirathan
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "uart.h"

int main(void)
{
    /* Replace with your application code */
	adc_init();
	uart_init();
    while (1) 
    {
		unsigned char ldr=getdata(0); 
		if(ldr>=0&&ldr<=25)
		{
			PORTB= 0x0F;
		}
		else
		{
			PORTB=0x00;
		}
		uart_string("LDR Value is : ");
		uart_num(ldr);
		uart_char('\n');
		_delay_ms(1000);
    }
}

