/*
 * ultra.c
 *
 * Created: 23-12-2019 14:15:06
 * Author : Bhahirathan
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart.h"
#include "adc.h"

#define US_PORT PORTC
#define	US_PIN	PINC
#define US_DDR 	DDRC

#define US_TRIG_POS	PC0
#define US_ECHO_POS	PC1
#define US_TRIG_POS1	PC2
#define US_ECHO_POS1	PC3


/********************************************************************

This function measures the width of high pulse in micro second.

********************************************************************/

#define US_ERROR		-1
#define	US_NO_OBSTACLE	-2

void HCSR04Init();
void HCSR04Trigger();

void HCSR04Init()
{
	US_DDR|=(1<<US_TRIG_POS);
}

void HCSR04Trigger()
{
	//Send a 10uS pulse on trigger line
	
	US_PORT|=(1<<US_TRIG_POS);	//high
	
	_delay_us(15);				//wait 15uS
	
	US_PORT&=~(1<<US_TRIG_POS);	//low
}

uint16_t GetPulseWidth()
{
	uint32_t i,result;

	//Wait for the rising edge
	for(i=0;i<600000;i++)
	{
		if(!(US_PIN & (1<<US_ECHO_POS)))
		continue;	//Line is still low, so wait
		else
		break;		//High edge detected, so break.
	}

	if(i==600000)
	return US_ERROR;	//Indicates time out
	
	//High Edge Found

	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);	//Prescaler = Fcpu/8
	TCNT1=0x00;			//Init counter

	//Now wait for the falling edge
	for(i=0;i<600000;i++)
	{
		if(US_PIN & (1<<US_ECHO_POS))
		{
			if(TCNT1 > 60000) break; else continue;
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;	//Indicates time out

	//Falling edge found

	result=TCNT1;

	//Stop Timer
	TCCR1B=0x00;

	if(result > 60000)
	return US_NO_OBSTACLE;	//No obstacle
	else
	return (result>>1);
}



void HCSR04Init1()
{
	US_DDR|=(1<<US_TRIG_POS1);
}

void HCSR04Trigger1()
{
	//Send a 10uS pulse on trigger line
	
	US_PORT|=(1<<US_TRIG_POS1);	//high
	
	_delay_us(15);				//wait 15uS
	
	US_PORT&=~(1<<US_TRIG_POS1);	//low
}

uint16_t GetPulseWidth1()
{
	uint32_t i,result;

	//Wait for the rising edge
	for(i=0;i<600000;i++)
	{
		if(!(US_PIN & (1<<US_ECHO_POS1)))
		continue;	//Line is still low, so wait
		else
		break;		//High edge detected, so break.
	}

	if(i==600000)
	return US_ERROR;	//Indicates time out
	
	//High Edge Found

	//Setup Timer1
	TCCR1A=0X00;
	TCCR1B=(1<<CS11);	//Prescaler = Fcpu/8
	TCNT1=0x00;			//Init counter

	//Now wait for the falling edge
	for(i=0;i<600000;i++)
	{
		if(US_PIN & (1<<US_ECHO_POS1))
		{
			if(TCNT1 > 60000) break; else continue;
		}
		else
		break;
	}

	if(i==600000)
	return US_NO_OBSTACLE;	//Indicates time out

	//Falling edge found

	result=TCNT1;

	//Stop Timer
	TCCR1B=0x00;

	if(result > 60000)
	return US_NO_OBSTACLE;	//No obstacle
	else
	return (result>>1);
}


void main()
{
	uint16_t r;
	int out1=0,out2=0;
	adc_init();
	uart_init();
	_delay_ms(100);	//Let the LCD Module start

	//Initialize the LCD Module
	
	//Set io port direction of sensor
	HCSR04Init();
	HCSR04Init1();
	_delay_ms(2500);


	while(1)
	{
		
		//Send a trigger pulse
		HCSR04Trigger();

		//Measure the width of pulse
		r=GetPulseWidth();

		//Handle Errors
		if(r==US_ERROR)
		{
			//LCDWriteStringXY(0,0,"Error !");
		}
		else if(r==US_NO_OBSTACLE)
		{
			//LCDWriteStringXY(0,0,"Clear !");
		}
		else
		{
			
			int d;

			d=(r/58.0)-1;	//Convert to cm
			out1=d;

			_delay_ms(500);
		}
		
		HCSR04Trigger1();
		//Measure the width of pulse
		r=GetPulseWidth1();

		//Handle Errors
		if(r==US_ERROR)
		{
			//LCDWriteStringXY(0,0,"Error !");
		}
		else if(r==US_NO_OBSTACLE)
		{
			//LCDWriteStringXY(0,0,"Clear !");
		}
		else
		{
			
			int d;

			d=(r/58.0)-1;
			out2=d;	//Convert to cm
			_delay_ms(500);
		}
		
		uart_num(out1);
		uart_string(" cm\t");
		uart_num(out2);
		uart_string(" CM\n");

	}
	
}
