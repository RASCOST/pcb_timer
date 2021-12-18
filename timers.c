/*
 * timer.c
 *
 * Created: 05-12-2014 18:31:10
 *  Author: RASC
 */ 
#include "timers.h"

extern volatile struct Clock clock = { 0, 0, 59 };

FLAG Flag;

extern volatile uint8_t	flag = NO_FLAG;
extern uint8_t isTimer1Stopped = 0;
extern uint8_t isBlink = 0;
extern uint8_t isZero = 0;

void timer0Init( void )
{
	//Enable T0 interrupt
	TIMSK0 |= ( 1 << TOIE0 );	
}

void timer1Init( void )
{
    TCCR1B |= ( 1 << WGM12 );
    OCR1A = 15625;
    TIMSK1 |= ( 1 << OCIE1A );
}

void timer2Init( void )
{
	//Asynchronous Timer2 Frequency 32.768kHz
	ASSR |= ( 1 << AS2 );
	
	//Overflow Interrupt Enable
	TIMSK2 |= ( 1 << TOIE2 );
}

/*
* Start T0 with Prescalar 64
* Clock 1MHz
*/
void timer0Start( void )
{
	TCCR0B |= ( 1 << CS01 ) | ( 1 << CS00 );
}

void timer0Stop( void )
{
	TCCR0B &= ~( ( 1 << CS01 ) | ( 1 << CS00 ) );
}

/*
* Start T1 with Prescalar 64
* Clock 1MHz
*/
void timer1Start( void )
{
	TCCR1B |= ( 1 << CS11 ) | ( 1 << CS10 );
}

void timer1Stop()
{
    TCCR1B &= ~( ( 1 << CS11 ) | ( 1 << CS10 ) );
}

void timer2Start( void )
{
	//Start Timer2 with Prescalar 128
	TCCR2B |= ( ( 1 << CS22 ) | ( 0 << CS21 ) | ( 1 << CS20 ) );
}

void timer2Stop( void )
{
	//Stop Timer2
	TCCR2B &= ~( ( 1 << CS22 ) | ( 1 << CS21 ) | ( 1 << CS20 ) );
}

void runTimer( void )
{
	if( !isZero )
	{
		if( clock.seg == 0 )
		{
			clock.seg = 59;
		
			if( clock.minu == 1 && clock.mind == 0 )
			{
				isZero = 1;
				isBlink = 1;
				clock.mind = 5;
				clock.minu = 9;
			}
			else if( clock.minu == 0 )
			{
				clock.mind--;
				clock.minu = 9;
			}
			else
				clock.minu--;
		}
		else
			clock.seg--;
	} 
	else
	{
		clock.seg--;
		
		if( clock.mind == 0 )
		{
			if( clock.minu == 0 )
			{
				//timer1Stop();
				timer2Stop();
				lightsOff();
				resetTimer();
				isTimer1Stopped = 1;
				isZero = 0;
				isBlink = 0;
			}
			else
				clock.minu--;
		} 
		else
		{
			if( clock.minu == 0 )
			{
				clock.mind--;
				clock.minu = 9;
			}
			else
				clock.minu--;
		}
	}
}

ISR( TIMER0_OVF_vect )
{
	flag = FLAG_Update7SegDisp;
}

ISR( TIMER1_COMPA_vect )
{
	TCNT1 = 0;
	flag = FLAG_RunTimer;
}

ISR( TIMER2_OVF_vect )
{
	flag = FLAG_RunTimer;
}

void setTimer( uint8_t direction )
{
	if( direction == 1 )
	{
		if( clock.minu == 9 )
		{
			if( clock.mind == 9 )
				return;
			else	
			{
				clock.mind++;
				clock.minu = 0;	
			}
		} 
		else
			clock.minu++;
	} 
	else
	{
		if( clock.minu == 0 )
		{
			if( clock.mind == 0 )
				return;
			else	
			{
				clock.mind--;
				clock.minu = 9;
			}
		} 
		else
			clock.minu--;
	}
}

void resetTimer( void )
{
	clock.mind = 0;
	clock.minu = 0;
	clock.seg = 59;
}

void setupTimer( void )
{
	if( clock.mind > 0 )
	{
		if( clock.minu > 0 )
			clock.minu--;
		else
		{
			clock.mind--;
			clock.minu = 9;
		}
	} 
	else
	{
		if( clock.minu == 1 )
		{
			isZero = 1;
			isBlink = 1;
			clock.mind = 5;
			clock.minu = 9;
		}
		else
		clock.minu--;
	}
}
