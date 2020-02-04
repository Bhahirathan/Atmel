/*
 * servomotor.c
 *
 * Created: 17-12-2019 22:12:04
 * Author : Bhahirathan
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"

#define MYP5 (5)
#define MYP4 (4)
#define MYP3 (3)
#define MYP2 (2)
#define MYP1 (1)
#define MYP0 (0)


int main(void)
{
	DDRB |= (1<<PB1);	/* Make OC1A pin as output */
	DDRD |=0xff;
	uart_init();
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */
	int co=65;
	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	while(1)
	{
		/*if(co==301)
		{
			co=65;
		}*/
		co=getdata(1);
		//OCR1A = co;	/* Set servo shaft at -90° position */
		_delay_ms(3000); 
		//co++;
		uart_num(co);
		uart_string("\n");
		//OCR1A = 175;	/* Set servo shaft at 0° position */
		//_delay_ms(5000);
		//OCR1A = 300;	/* Set servo at +90° position */
		//_delay_ms(5000);
	}
}

