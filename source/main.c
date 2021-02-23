/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "bit.h"
#include "scheduler.h"
#include "keypad.h"
#include "timer.h"

#endif

unsigned char b = 0x00;

enum states{start};

int tick(int state){
	unsigned char but;
	but = GetKeypadKey();
	switch(state){

	case start:
		switch(but){
			case '\0': b = 0x1F; break;
			case '1' : b = 0x01;break;
			case '2' : b = 0x02;break;
			case '3' : b = 0x03;break;
			case '4' : b = 0x04;break;
			case '5' : b = 0x05;break;
			case '6' : b = 0x06;break;
			case '7' : b = 0x07;break;
				   case '8' : b = 0x08;break;
				case '9' : b = 0x09;break;
				case 'A' : b = 0x0A;break;
				case 'B' : b = 0x0B;break;
				case 'C' : b = 0x0C;break;
				case 'D' : b = 0x0D;break;
				case '*' : b = 0x0E;break;
				case '#' : b = 0x0F;break;
				case '0' : b = 0x00;break;
				default: b = 0x1B; break;
		}

	state = start;
	PORTB = b;
	break;
	}
	return state;
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	

    task1.state = 0;
    task1.period = 2;
    task1.elapsedTime = 2;
    task1.TickFct = &tick;

    TimerSet(10);
    TimerOn();
	unsigned short i;
   	while(1) {
   		for ( i = 0; i < numTasks; i++ ) {
   			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
   				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
   				tasks[i]->elapsedTime = 0;
   			}
   			tasks[i]->elapsedTime += 1;
   		}
   		while(!TimerFlag);
   		TimerFlag = 0;
   	}



    return 1;
}
