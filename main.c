/*
 * MDKnocker.c
 *
 * Created: 2/26/2016 9:46:02 PM
 * Author : Mike
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define RED_LED (1<<1)
#define GREEN_LED (1<<2)
#define MODE_TOGGLE 0
#define PULSE_TIME 500

/*
	Modes:
	Bit 1 - Programming or Listening
*/
unsigned char Mode = 0x01;


#define MODE_PROGRAMMING (1<<0);

unsigned int counter = 0;

void PulsePin(unsigned char PIN, int times) {
	for (int i=0;i<times;i++)
	{
		PORTB |= PIN;
		_delay_ms(PULSE_TIME);
		PORTB &= ~PIN;
		_delay_ms(PULSE_TIME);
	}
}

ISR(TIMER1_COMPA_vect) {
	counter++;
	
	if (counter>100) {
		PulsePin(RED_LED, 1);
		counter = 0;
	}
}

int main(void)
{
	/*
		Pin0 - Knocker
		Pin1 - Green LED
		Pin2 - Red LED
	*/
	sei();
		
	OCR1A = 195;
	TIMSK = (1<<OCIE1A);
	TCCR1 = (1<<CTC1) | (0b1000);		// CTC On, 1024 Pre Scale, No Pin Triggering, No PWM
	
	DDRB = (0<<DDB0) | (1<<DDB1) | (1<<DDB2);
	PORTB = 0x0 | (1<<MODE_TOGGLE);
	
	//PulsePin(RED_LED, 2);
	
    /* Replace with your application code */
    while (1) 
    {
		
		/*
		if ((PINB & (1<<MODE_TOGGLE))) {
			PulsePin(RED_LED, 1);
		} else {
			PulsePin(GREEN_LED, 1);
		}
		*/
    }
}

