/*
 * init.h
 *
 * Created: 6/17/2016 1:56:52 PM
 *  Author: Anil Gawali
 */ 


#ifndef INIT_H_
#define INIT_H_

#define F_CPU 8000000UL

#define sbit(reg,bit) reg |=(1<<bit)     // set bit i.e. give bit high
#define cbit(reg,bit) reg &= ~(1<<bit)   // clear bit i.e. give bit low
#define check(reg,bit) ((reg & (1<<bit))?1:0)

#include <util/delay.h>

#define ADC_VREF_TYPE 0x20
#include <string.h>

// Read the 8 most significant bits
// of the AD conversion result
unsigned char read_adc(unsigned char adc_input)
{
	ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=0x40;
	// Wait for the AD conversion to complete
	while ((ADCSRA & 0x10)==0);
	ADCSRA|=0x10;
	return ADCH;
}

// Declare your global variables here

void port(void)
{
	// Declare your local variables here

	// Input/Output Ports initialization
	// Port A initialization
	// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=Out
	// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=0
	PORTA=0x00;
	DDRA=0x01;

	// Port B initialization
	// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
	// State7=0 State6=0 State5=0 State4=0 State3=0 State2=1 State1=0 State0=0
	PORTB=0x00;
	DDRB=0xFF;

	// Port C initialization
	// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
	// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
	PORTC=0x00;
	DDRC=0xFF;
	
	
	// Port D initialization
	// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
	// State7=1 State6=0 State5=1 State4=0 State3=0 State2=0 State1=0 State0=0
	PORTD=0x00;
	DDRD=0xFF;
}

void timer()
{
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 31.250 kHz
	// Mode: Fast PWM top=0xFF
	// OC0 output: Non-Inverted PWM
	TCCR0=0x6C;
	TCNT0=0x00;
	OCR0=0x00;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: Timer1 Stopped
	// Mode: Normal top=0xFFFF
	// OC1A output: Discon.
	// OC1B output: Discon.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;

	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: 125.000 kHz
	// Mode: Fast PWM top=0xFF
	// OC2 output: Non-Inverted PWM
	ASSR=0x00;
	TCCR2=0x6C;
	TCNT2=0x00;
	OCR2=0x00;

	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	// INT2: Off
	MCUCR=0x00;
	MCUCSR=0x00;

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x00;

	// USART initialization
	// USART disabled
	UCSRB=0x00;

	// Analog Comparator initialization
	// Analog Comparator: Off
	// Analog Comparator Input Capture by Timer/Counter 1: Off
	ACSR=0x80;
	SFIOR=0x00;

	// ADC initialization
	// ADC Clock frequency: 125.000 kHz
	// ADC Voltage Reference: AREF pin
	// ADC Auto Trigger Source: Free Running
	// Only the 8 most significant bits of
	// the AD conversion result are used
	ADMUX=ADC_VREF_TYPE & 0xff;
	ADCSRA=0x83;
	SFIOR&=0x1F;

	// SPI initialization
	// SPI disabled
	SPCR=0x00;

	// TWI initialization
	// TWI disabled
	TWCR=0x00;

	
}

void forward(int d1,int d2)
{
	OCR0 =d1;   // LEFT MOTOR PWM
	OCR2=d2;  // RIGHT MOTOR PWM
	sbit(PORTD,5);
	cbit(PORTD,6);
	sbit(PORTC,1);
	cbit(PORTC,0);
}

void backward(void)
{
	OCR0 =87;   // LEFT MOTOR PWM
	OCR2=138;  // RIGHT MOTOR PWM
	sbit(PORTD,6);
	cbit(PORTD,5);
	sbit(PORTC,0);
	cbit(PORTC,1);
}

void right90(void)
{
	OCR0 =87;   // LEFT MOTOR PWM
	OCR2=138;  // RIGHT MOTOR PWM
		cbit(PORTD,5);
		sbit(PORTD,6);
		sbit(PORTC,1);
		cbit(PORTC,0);
}

void left90(void)
{
	OCR0 =87;   // LEFT MOTOR PWM
	OCR2=138;  // RIGHT MOTOR PWM
	sbit(PORTD,5);  // left wheel
	cbit(PORTD,6);
	cbit(PORTC,1); // right wheel
	sbit(PORTC,0);
}
void left(void)
{
	OCR0 =87;   // LEFT MOTOR PWM
	OCR2=170;  // RIGHT MOTOR PWM
	sbit(PORTD,5);
	cbit(PORTD,6);
	cbit(PORTC,1);
	cbit(PORTC,0);
}

void right()
{
	OCR0 =87;   // LEFT MOTOR PWM
	OCR2=170;  // RIGHT MOTOR PWM
	cbit(PORTD,5);
	cbit(PORTD,6);
	sbit(PORTC,1);
	cbit(PORTC,0);
}
void stop()
{
	OCR0 =87;   // LEFT MOTOR PWM
	OCR2=135;  // RIGHT MOTOR PWM
	cbit(PORTD,5);
	cbit(PORTD,6);
	cbit(PORTC,1);
	cbit(PORTC,0);
}

/*void slightright(void)
{
		OCR0 =60;   // LEFT MOTOR PWM
		OCR2=40;  // RIGHT MOTOR PWM
		cbit(PORTD,5);
		cbit(PORTD,6);
		sbit(PORTC,1);
		cbit(PORTC,0);

}
void slightleft(void)
{
	OCR0 =40;   // LEFT MOTOR PWM
	OCR2=60;  // RIGHT MOTOR PWM
	cbit(PORTD,5);
	sbit(PORTD,6);
	cbit(PORTC,1);
	cbit(PORTC,0);

}*/

#endif /*INCFILE1_H_*/	