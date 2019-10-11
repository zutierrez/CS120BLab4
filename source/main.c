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

enum States { SLED_START, SLED_ONOF , SLED_SWITCH } state;

void SwitchLED(state)
{
	switch(state) {      //TRANSITIONS
	    
	    case SLED_START:
		state = SLED_ONOF;
		break;
	
	    case SLED_ONOF:
	       if(PINA == 0x00){		
		state = SLED_ONOF;
	       }
	       else if(PINA == 0x01){		
		state = SLED_SWITCH;
	       }
	       break;

	    case SLED_SWITCH:
	       if(PINA == 0x00){		
		state = SLED_SWITCH;
	       }
	       else if(PINA == 0x01){		
		state = SLED_ONOF;
	       }
	       break;
	    
	    default:
	        state = SLED_ONOF;
	       break;
	
	}

	switch(state) {      //ACTIONS
	    
	    case SLED_START: 
		break; 

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
	
        while (1) {
	// inputs:
	enum States state = SLED_START;

	SwitchLED(state);

        // outputs:
        }  
 return 1;
}
