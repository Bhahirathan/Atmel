/*
 * test2.c
 *
 * Created: 29-12-2019 22:18:15
 * Author : Bhahirathan
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"



int main(void)
{
	DDRB|=0xff;
	adc_init();
	uart_init();
	unsigned char r,r1,co=0,co1=0,t=0;
			uart_string("AT+RST\r\n");
			_delay_ms(5000);
			
			uart_string("ATE0\r\n");
			
			uart_string("AT+CWMODE_DEF=3\r\n");
			_delay_ms(100);
			
			//_delay_ms(100);
			//uart_string("AT+CIPSTO=10");
			uart_string("AT+CWJAP_DEF=\"test\",\"12345678\"\r\n");
			//uart_string("AT+CIPSTO=100");
			_delay_ms(5000);
    /* Replace with your application code */
    while (1) 
    {
		t=r1;
		r1=getdata(0);
		r=getdata(1);
		/*uart_num(r);
		uart_string("\t");*/
		uart_num(r1);
		//uart_string("\n");
		_delay_ms(14000);
		if(r1<20)
		{
			co1++;
		}
		else 
		{
			co1=0;
		}
		if(co1==10)
		{
			co1=0;
			PORTB|=(1<<5);
			//uart_string("Out of Labour");
			_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);_delay_ms(14000);
			PORTB&=~(1<<5);
		}
		uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
		_delay_ms(2000);
		uart_string("AT+CIPSEND=51\r\n");
		_delay_ms(100);
		uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field7=");
		uart_num(r);
		uart_string("\r\n");
		_delay_ms(100);
		uart_string("AT+CIPCLOSE\r\n");
	}
}

