/*
 * light.c
 *
 * Created: 24-07-2015 14:04:45
 *  Author: RASC
 */ 
#include "light.h"

void lightsOn( void )
{
	PORTC |= ( 1 << PC2 );
}

void lightsOff( void )
{
	PORTC &= ~( 1 << PC2 );
}
