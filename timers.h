/*
 * timer.h
 *
 * Created: 05-12-2014 18:30:57
 *  Author: RASC
 */ 


#ifndef TIMER_H
#define TIMER_H

#include <avr/interrupt.h>
#include "7seg.h"
#include "light.h"

struct Clock
{
    uint8_t mind;
    uint8_t minu;
	uint8_t seg;
};

volatile struct Clock clock;

typedef enum { NO_FLAG, FLAG_Update7SegDisp, FLAG_RunTimer} FLAG;
extern FLAG Flag;
volatile uint8_t flag;
uint8_t isTimer1Stopped;
uint8_t isBlink;
uint8_t isZero;


void timer0Init( void );
void timer1Init( void );
void timer2Init( void );
void timer0Start( void );
void timer0Stop( void );
void timer1Start( void );
void timer1Stop( void );
void timer2Start( void );
void timer2Stop( void );
void runTimer( void );
ISR( TIMER0_OVF_vect );
ISR( TIMER1_COMPA_vect );
ISR( TIMER2_OVF_vect );
void setTimer( uint8_t direction );
void resetTimer( void );
void setupTimer( void );

#endif /* TIMER_H */