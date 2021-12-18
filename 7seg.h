/*
 * _7seg.h
 *
 * Created: 24-11-2014 19:41:12
 *  Author: RASC
 */ 

#ifndef DISP7SEG_H
#define DISP7SEG_H

#include <avr/io.h>
#include <util/delay.h>
#include "timers.h"

#define DISP_7_SEG PORTD
#define CTRL_7SEG_DISP PORTC

#define CRTL_D_MIN PC1
#define CRTL_U_MIN PC0

#define BIT( x ) ( 1 << x )
#define CLR_CTRLS() ( CTRL_7SEG_DISP  &= ~0x03 )
#define SET_D_MIN() ( CTRL_7SEG_DISP |= BIT( CRTL_D_MIN ) )
#define SET_U_MIN() ( CTRL_7SEG_DISP |= BIT( CRTL_U_MIN ) )

enum Digit{ MIN_U, MIN_D };
enum Digit digit;

volatile struct Clock clock;
volatile uint8_t blinkTick;
volatile uint8_t isOn;

uint8_t convertTo7SegDisp( uint8_t c );
void update7SegDisp( void );
void blink7SegDisp( void );

#endif /* 7SEG_H */