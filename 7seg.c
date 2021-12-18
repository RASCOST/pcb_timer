/*
 * _7seg.c
 *
 * Created: 24-11-2014 19:41:35
 *  Author: RASC
 */

/*
*      a 
*  __________
* |          |
* |f         |b
* |    g     |
* |__________|
* |          |
* |          |c
* |e   d     |  _
* |__________| |_|dp
*
*/ 
#include "7seg.h"

enum Digit digit = MIN_U;
extern volatile struct Clock clock;

volatile uint8_t blinkTick = 0;
volatile uint8_t isOn = 0;

uint8_t convertTo7SegDisp( uint8_t c )
{
    unsigned char conversion = 0;
    
    switch( c )
    {
        case 0:
            conversion = 0x3F;
            break;
        case 1:
            conversion = 0x06;
            break;
        case 2:
            conversion = 0x5B;
            break;
        case 3:
            conversion = 0x4F;
            break;
        case 4:
            conversion = 0x66;
            break;
        case 5:
            conversion = 0x6D;
            break;
        case 6:
            conversion = 0x7D;
            break;
        case 7:
            conversion = 0x07;
            break;
        case 8:
            conversion = 0x7F;
            break;
        case 9:
            conversion = 0x67;
            break;
    }
    
    return conversion;
}

void update7SegDisp()
{	 
	 switch( digit )
	 {
		 case MIN_U:
					digit = MIN_D;
                    CLR_CTRLS();
                    DISP_7_SEG = ( 0x80 & DISP_7_SEG ) | convertTo7SegDisp( clock.minu );
                    SET_U_MIN();
		 break;
		 
		 case MIN_D:
					digit = MIN_U;
                    CLR_CTRLS();
                    DISP_7_SEG = ( 0x80 & DISP_7_SEG ) | convertTo7SegDisp( clock.mind );
                    SET_D_MIN();
		 break;
	 }
}

void blink7SegDisp()
{
	if( blinkTick == 16 )
	{
		blinkTick = 0;
		
		if( isOn )
			isOn = 0; 
		else
			isOn = 1;
	}		
	else
	{
		blinkTick++;
		
		if( isOn )
			update7SegDisp();
		else
			CLR_CTRLS();
	}
}	
