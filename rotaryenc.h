/*
 * rotaryenc.h
 *
 * Created: 11-02-2015 18:44:40
 *  Author: RASC
 */ 


#ifndef ROTARYENC_H_
#define ROTARYENC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timers.h"

#define ROTARY_UP 0xFD
#define ROTARY_DOWN 0xFB
#define ROTARY_ENTER 0xFE
#define ROTARY PINB
#define ENTER_MASK 0x01

volatile uint8_t state;

void initExtInt( void );
void enableExtInt( void );
void disableExtInt( void );
ISR( PCINT0_vect );

#endif /* ROTARYENC_H_ */