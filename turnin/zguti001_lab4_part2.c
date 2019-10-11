/*	Author: Zion Gutierrez, zguti001
 *      Partner(s) Name: none
 *	Lab Section: 023
 *	Assignment: Lab #4 Exercise #2
 *	Exercise Description: INCREMENTER AND DECREMENTER 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { START7 , INCREMENT, DECREMENT, RESET } state;
unsigned char cnt = 0x07;
#define inputA PINA

void SM(state)
{
	switch(state) {      //TRANSITIONS
	

		case START7:
	       		if ( inputA == 0x01 ){
				if( cnt >= 0 && cnt < 9){
					state = INCREMENT;
				}
	       		}
			else if( inputA == 0x02 ){
				if( cnt >= 0 && cnt < 10){
					state = DECREMENT;
				}
			}
			else if( inputA == 0x03 ){
				state = RESET;
			}
			else { state = START7; }
	       		break;

	    	case INCREMENT:
			state = START7;
	       		break;
	    
	   	case DECREMENT:
			state = START7;
			break;

		case RESET:
			state = START7;
			break;

		default:
	        	state = START7;
	       		break;	
		}	

	switch(state) {      //ACTIONS
	    
	    	case START7:		
			break;
	    	case INCREMENT:
			++cnt;
			inputA = 0x00;
			break;
		case DECREMENT:
			--cnt;
			inputA = 0x00;
			break;
		case RESET:
			cnt = 0x00;
			inputA = 0x00;
			break;
		}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port C's 8 pins as inputs, initialize to 0s
     	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 7 most significant pins as outputs and PB0 as input
	
	enum States state = START7;
        
	while(1){ 

	SM(state);
	
	PORTC = cnt;
	}  
	return 1;
}
