/*
 * buzzz.c
 *
 * Created: 18-10-2019 15:19:34
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
#define US_TRIG_POS1	PC0
#define US_ECHO_POS1	PC3

#define MYP5 (5)
#define MYP4 (4)
#define MYP3 (3)
#define MYP2 (2)
#define MYP1 (1)
#define MYP0 (0)

#define US_ERROR		-1
#define	US_NO_OBSTACLE	-2

//Ultrasonic
uint16_t r;
int out1=0,out2=0;


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
int i=525;
void mydelay6()
{
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
}
int checkChemical()
{
			HCSR04Trigger();
			_delay_ms(5000);
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
			
		//	uart_num(out1);
			//uart_string(" cm\t");
			//uart_num(out2);
			//uart_string(" CM\n");
			
		if(out1!=7)	
			uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
			_delay_ms(2000);
			uart_string("AT+CIPSEND=51\r\n");
			_delay_ms(100);
			uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field1=");
			uart_num(out1);
			uart_string("\r\n");
			_delay_ms(100);
			uart_string("AT+CIPCLOSE\r\n");
			
		if(out2!=6)	
			uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
			_delay_ms(2000);
			uart_string("AT+CIPSEND=51\r\n");
			_delay_ms(100);
			uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field2=");
			uart_num(out2);
			uart_string("\r\n");
			_delay_ms(100);
			uart_string("AT+CIPCLOSE\r\n");
			
			
if(out2==6&&out1==7){
			PORTD |= (1<<7);
			mydelay6();				
			uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
			_delay_ms(2000);
			uart_string("AT+CIPSEND=51\r\n");
			_delay_ms(100);
			uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field2=");
			uart_num(out2);
			uart_string("\r\n");
			_delay_ms(100);
			uart_string("AT+CIPCLOSE\r\n");
	mydelay6();
	uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	_delay_ms(2000);
	uart_string("AT+CIPSEND=51\r\n");
	_delay_ms(100);
	uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field1=");
	uart_num(out1);
	uart_string("\r\n");
	_delay_ms(100);
	uart_string("AT+CIPCLOSE\r\n");

return 1;
}
else
return 0;
}


int main(void)
{  
			HCSR04Init();
		HCSR04Init1();
		_delay_ms(2500);

	
	DDRB |=0xff;
	DDRD |=0xff;
		TCNT1 = 0;		/* Set timer1 count zero */
		ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */
		/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
		TCCR1A = (1<<WGM11)|(1<<COM1A1);
		TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
		
	int f1=0;
	unsigned char chemcheck,val=150,ldr=0,ir=0,temp=0;
	   adc_init();
	   uart_init();
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
		if(f1==0)
		{
		PORTB |= (1<<MYP5);
		chemcheck=checkChemical();
		OCR1A = i;
		i=i-3;
		}
		if(f1==1)
		{
			ldr=getdata(2);
		}
		if(f1==2)
		{
			ir=getdata(4);
		}
		if(f1==3)
		{
			temp=getdata(5);
		}
		if(f1==0&&chemcheck==1)
		{
			PORTB |= (1<<MYP4);
			OCR1A = 525;
			PORTB &= ~(1<<MYP5);
			f1=1;
		}
		else if(f1==1&&ldr>50)
		{
			PORTB |= (1<<MYP0);
			_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);_delay_ms(11000);
	
			uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
			_delay_ms(2000);
			uart_string("AT+CIPSEND=51\r\n");
			_delay_ms(100);
			uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field4=");
			uart_num(val);
			uart_string("\r\n");
			_delay_ms(100);
			uart_string("AT+CIPCLOSE\r\n");
			_delay_ms(11000);
			mydelay6();
			
			PORTB |= (1<<MYP3);
			PORTB |= (1<<MYP0);
			PORTB &= ~(1<<MYP4);
			f1=2;
		}
		else if(f1==2&&ir==35)
		{
			PORTD |= (1<<5);
			uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
			_delay_ms(2000);
			uart_string("AT+CIPSEND=51\r\n");
			_delay_ms(100);
			uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field5=");
			uart_num(ir);
			uart_string("\r\n");
			_delay_ms(100);
			uart_string("AT+CIPCLOSE\r\n");
			_delay_ms(11000);	
			
			mydelay6();
			PORTB |= (1<<MYP2);
			PORTB &= ~(1<<MYP3);
			f1=3;
		}
		if (f1==3&&temp>80)
		{
						PORTD |= (1<<6);
						uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
						_delay_ms(2000);
						uart_string("AT+CIPSEND=51\r\n");
						_delay_ms(100);
						uart_string("GET /update?api_key=Z4B99CJDP1FQ6640&field6=");
						uart_num(temp);
						uart_string("\r\n");
						_delay_ms(100);
						uart_string("AT+CIPCLOSE\r\n");
						_delay_ms(11000);
						mydelay6();
						PORTD |= (1<<6);
						PORTB &= ~(1<<MYP2);
		}
		//PORTB |= (1<<MYP5);
		//_delay_ms(2000);
		//PORTB &= ~(1<<MYP5);
		//_delay_ms(2000); 
		
    }
	
}

