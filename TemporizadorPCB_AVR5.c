/*
 * TemporizadorPCB_AVR5.c
 *
 * Created: 08-02-2015 15:17:54
 *  Author: RASC
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "timers.h"
#include "7seg.h"
#include "rotaryenc.h"
#include "light.h"

extern volatile struct Clock clock;

FLAG Flag;
extern volatile uint8_t flag;
extern uint8_t isBlink;
extern uint8_t isZero;
enum{ STOP, SET, RUN };


uint8_t switchState = 1;
uint8_t isSetting = 0;

/*
*
*/
void debounce( void )
{
	//static uint8_t count = 0;	 
	isSetting = 1;
	uint8_t currentState = ROTARY & ENTER_MASK;
	
	if( currentState == 0 )
	{
		timer0Stop();
		CLR_CTRLS();
		_delay_ms( 25 );
		if( currentState == 0 )
		{
			switchState = 0;
		}
		else
		{
			switchState = 1;
		}
		_delay_ms( 250 );
	} 
	else
	{
		switchState = 1;
	}
	isSetting = 0;
	timer0Start();
}

int main( void )
{
    //DDRD = 0x7F;
	DDRD |= ( 1 << PD6 ) | ( 1 << PD5 ) | ( 1 << PD4 ) | ( 1 << PD3 ) | ( 1 << PD2 ) | ( 1 << PD1 ) | ( 1 << PD0 );
    //DDRC = 0x03;
	DDRC |= ( 1 << PC2 ) | ( 1 << PC1 ) | ( 1 << PC0 );
    
	uint8_t timerState = SET;
		
	timer0Init();
 	timer2Init();
	initExtInt();
	
	sei();
	
    timer0Start();
	
    while( 1 )
    {		 
		 switch( flag )
		 {
			case FLAG_Update7SegDisp:
				flag = NO_FLAG;
 
				if( !isBlink )
					update7SegDisp(); 
				else
				{
					blink7SegDisp();
				}
			break;
			
			case FLAG_RunTimer:
				flag = NO_FLAG;
				runTimer();
			break;
			
			case NO_FLAG:
				debounce();
				
				if( !switchState )
				{
					
					if( isTimer1Stopped && timerState == STOP )
					{
						timerState = SET;
						isTimer1Stopped = 0;
					}

					switch( timerState )
					{
						case STOP:
							if( isZero )
							{
								isZero = 0;
								isBlink = 0;
							}
							timerState = SET;
							timer2Stop();
							resetTimer();
							lightsOff();
						break;
						
						case SET:
							timerState = RUN;
							isBlink = 1;
							enableExtInt();
						break;
						
						case RUN:
							isBlink = 0;
							disableExtInt();
							if( clock. mind == 0 && clock.minu == 0 )
							{
								timerState = SET;
							} 
							else
							{
								timerState = STOP;
								setupTimer();
								timer2Start();
								lightsOn();
							}
							
						break;
					}
				}
			break;
			 
		 }
    }
}
