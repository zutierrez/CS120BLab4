/*	Author: Zion Gutierrez, zguti001
 *      Partner(s) Name: none
 *	Lab Section: 023
 *	Assignment: Lab #4 Exercise #1
 *	Exercise Description: LED & BUTTON 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define inputA PINA

enum SLED_States { SLED_Start, SLED_ONOF , SLED_SWITCH } SLED_State;

void SwitchLED(SLED_State)
{
	switch(SLED_State) {      //TRANSITIONS
		
	    case SLED_Start:      //initial transition
		SLED_State = SLED_ONOF;
		break;
	    
	    case SLED_ONOF:
	       if(inputA == 0x00){		
		SLED_State = SLED_ONOF;
	       }
	       else if(inputA == 0x01){		
		SLED_State = SLED_SWITCH;
	       }
	       break;

	    case SLED_SWITCH:
	       if(inputA == 0x00){		
		SLED_State = SLED_SWITCH;
	       }
	       else if(inputA == 0x01){		
		SLED_State = SLED_ONOF;
	       }
	       break;
	    
	    default:
	        SLED_State = SLED_Start;
	       break;
	}
	switch(SLED_State) {      //ACTIONS
	    
	    case SLED_ONOF:		
		PORTB = 0x02;
		break;

	    case SLED_SWITCH:
		PORTB = 0x01;
		break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port C's 8 pins as inputs, initialize to 0s
     	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 7 most significant pins as outputs and PB0 as input
	unsigned char outputB = 0x00;

        while (1) {
	// inputs:
	
	SwitchLED(SLED_State);

        // outputs:
	PORTB = outputB;
        } 
  return 1;
}
