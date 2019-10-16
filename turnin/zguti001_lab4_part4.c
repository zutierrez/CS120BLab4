/*	Author: Zion Gutierrez, zguti001
 *      Partner(s) Name: none
 *	Lab Section: 023
 *	Assignment: Lab #4 Exercise #4
 *	Exercise Description: DOOR LOCK & CODE for LOCKING AND UNLOCKING 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { LOCKED, PRESS_PND, RELEASE_PND, PRESS_Y, RELEASE_Y, UNLOCKED } state;
unsigned char outputB = 0x00;
unsigned char outputC = 0x00;
unsigned char inputA = 0x00;

void SM()
{
	switch(state) {      //TRANSITIONS
	
		case LOCKED:
			outputB = 0x00;
	       		if( inputA == 0x04 ){
				state = PRESS_PND; }
			else { state = LOCKED; }
	       		break;

	    	case PRESS_PND:
			if( inputA == 0x04 ){
				state = PRESS_PND; }
			else if( inputA == 0x00) {
				 state = RELEASE_PND; } 
	       		break;
	
		case RELEASE_PND:
			if( outputB == 0x01 ){          //if unlocked wait for Y 
				if( inputA == 0x02 ){	//but if wrong go back to unlocked
				 	state = PRESS_Y; }
				else if( inputA == 0x01 || inputA == 0x04){
					state = UNLOCKED; }
				else{ state = RELEASE_PND; }
			}
			else if( outputB == 0x00 ){    //if locked wait for Y
				if( inputA == 0x02 ){  //but if wrong go back to locked
					state = PRESS_Y; }
				else if( inputA == 0x01 || inputA == 0x04){
					state = LOCKED; }
				else { state = RELEASE_PND; }
			} 
				break;

		case PRESS_Y:
			if( outputB == 0x01 ){ 
				if( inputA == 0x02 ){
					state = PRESS_Y; }
				else if( inputA == 0x00 ){
					state = RELEASE_Y; }
				else { state = UNLOCKED; }
			}
			else if( outputB == 0x00 ){
				if( inputA == 0x02 ){
                                        state = PRESS_Y; }
                                else if( inputA == 0x00 ){
                                        state = RELEASE_Y;}
                                else { state = LOCKED; }

			}
			break;
	
		case RELEASE_Y:
			if( outputB == 0x01 ){
				state = LOCKED;}
			else if( outputB == 0x00) {
				state = UNLOCKED;} 
			break;
 
		case UNLOCKED:
			outputB =  0x01;
			if( inputA == 0x80 ){
				state = LOCKED; }
			else if( inputA = 0x04 ){
				state = PRESS_PND;}
			else { state = UNLOCKED; }
			break;

		default:
			state = LOCKED;
			break;	
		}


	switch(state) {      //ACTIONS
	    
	    	case LOCKED:
			outputB = 0x00;
			outputC = state;		
			break;
	    	case PRESS_PND:
			outputC = state;
			break;
		case RELEASE_PND:
			outputC = state;
			break;
		case PRESS_Y:
			outputC = state;
			break;
		case RELEASE_Y:
			outputC = state;
			break;
		case UNLOCKED:
			outputB = 0x01;
			outputC = state;
			break;
		}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A as input
     	DDRB = 0xFF; PORTB = 0x00; // Configure port B as output
	DDRC = 0xFF; PORTC = 0x00; // Configure port C as output
	
	enum States state = LOCKED;
        
	while(1){ 
	//input:
	inputA = PINA;

	SM();
	PORTB = outputB;
	}  

	return 1;
}
