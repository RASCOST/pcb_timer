/*
 * rotaryenc.c
 *
 * Created: 11-02-2015 18:45:05
 * Author: RASC
 */ 
#include "rotaryenc.h"

enum{ START, CW_STEP1, CW_STEP2, CW_STEP3, CCW_STEP1, CCW_STEP2, CCW_STEP3 };
	
volatile uint8_t state = START;

void initExtInt( void )
{
	PCMSK0 |= ( 1 << PCINT2 ) | ( 1 << PCINT1 );
}

void enableExtInt( void )
{
	PCICR |= ( 1 << PCIE0 );
}

void disableExtInt( void )
{
	PCICR &= ~( 1 << PCIE0 );
}

ISR( PCINT0_vect )
{
	uint8_t input = ( ROTARY & 0x06 );
	
	switch( input )
	{
		case 0x00:
			if( state == CW_STEP1 )
			{
				state = CW_STEP2;
			} 
			else if( state == CCW_STEP1 )
			{
				state = CCW_STEP2;
			}
			else
				state = START;
		break;
		
		case 0x02:
			if( state == CW_STEP2 )
			{
				state = CW_STEP3;
			} 
			else if( state == START )
			{
				state = CCW_STEP1;
			}
			else
				state = START;
		break;
		
		case 0x04:		
			if( state == START )
			{
				state = CW_STEP1;
			} 
			else if( state == CCW_STEP2 )
			{
				state = CCW_STEP3;
			}
			else
				state = START;
		break;
		
		case 0x06:
			if( state == CW_STEP3 )
			{
				state = START;
				setTimer( 0 );
			} 
			else if( state == CCW_STEP3 )
			{
				state = START;
				setTimer( 1 );
			}
			else
				state = START;
		break;
		
		default:
			state = START;	
	}
}	
