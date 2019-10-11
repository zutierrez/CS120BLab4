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

enum States { SLED_INIT , SLED_SWITCH_PRESS, SLED_SWITCH_RELEASE, SLED_INIT_PRESS } state;
unsigned char outputB = 0x00;
unsigned char inputA = 0x00;

void SwitchLED(state)
{
	switch(state) {      //TRANSITIONS
	
		case SLED_INIT:
			outputB = 0x01;
	       		if (inputA == 0x01){		
				outputB = 0x02;
				state = SLED_SWITCH_PRESS;
	       		}
			else if(inputA == 0x00) {
                                state = SLED_INIT;
                        }
	       		break;

	    	case SLED_SWITCH_PRESS:
			if( inputA == 0x01 ){		
				state = SLED_SWITCH_PRESS;
	       		}
			else if ( inputA == 0x00) {
                                state = SLED_SWITCH_RELEASE;
                        }
	       		break;
	    
	   	case SLED_SWITCH_RELEASE:
			if( inputA == 0x00 ){
                                state = SLED_SWITCH_RELEASE;
                        }
			else if( inputA == 0x01) {
				outputB = 0x01;
				state = SLED_INIT_PRESS;
			}
			break;

		case SLED_INIT_PRESS:
			if( inputA == 0x01){
				state = SLED_INIT_PRESS;
			}
			else if( inputA ==  0x00) {
				state = SLED_INIT;
			}
			break;

		default:
	        	state = SLED_INIT;
	       		break;	
		}	

	switch(state) {      //ACTIONS
	    
	    	case SLED_INIT:		
			break;
	    	case SLED_SWITCH_PRESS:
			outputB = 0x02;
			break;
		case SLED_SWITCH_RELEASE:
			break;
		case SLED_INIT_PRESS:
			outputB = 0x01;
			break;
		}
	}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port C's 8 pins as inputs, initialize to 0s
     	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 7 most significant pins as outputs and PB0 as input
	
	//enum States state = SLED_INIT;
        
	while (1) {
	inputA = PINA;

	SwitchLED(state);
	
	PORTB = outputB;
	}  
	return 1;
}
