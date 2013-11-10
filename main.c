/*
 * main.c
 * Created on: Nov 6, 2013
 * Author: Linnea Larson
 * Description- calls functions to play cursor game
 */

#include <msp430.h>
#include "LCD/Lab4_LCD.h"
#include "game.h"
#include "buttons/button.h"
unsigned char flag = 0;
unsigned char flag2 = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    TACTL &= ~(MC1|MC0);        // stop timer

    TACTL |= TACLR;             // clear TAR

    TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

    TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

    TACTL &= ~TAIFG;            // clear interrupt flag

    TACTL |= MC1;               // set count mode to continuous

    TACTL |= TAIE;              // enable interrupt

    __enable_interrupt();       // enable maskable interrupts

    char myString1[] = "You";
    char myString2[] = "Win!";
    char myString3[] = "Game";
    char myString4[] = "Over";
    char myString1Length = 3;
    char myString2Length = 4;
    char myString3Length = 4;
    char myString4Length = 4;
    int player = 0;


    initSPI();

    LCDinit();

    LCDclear();

    unsigned char location = initPlayer();

    printPlayer(location);

    configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);

    while (1) {

    	if (isP1ButtonPressed (BIT1)) {
    		location = movePlayer (location, UP);
    		flag = 0;
    	}
    	if (isP1ButtonPressed (BIT2)) {
    		location = movePlayer (location, DOWN);
    		flag = 0;
    	}
    	if (isP1ButtonPressed (BIT3)) {
    		location = movePlayer (location, RIGHT);
    		flag = 0;
    	}
    	if (isP1ButtonPressed (BIT4)) {
    		location = movePlayer (location, LEFT);
    		flag = 0;
    	}
    	unsigned char winner = didPlayerWin(location);
    	while (winner){
    		clearPlayer (location);
    		cursorToLineOne ();
    		writeString (myString1, myString1Length);
    		cursorToLineTwo ();
    		writeString (myString2, myString2Length);
    		if (isP1ButtonPressed (BIT1)) {
    			LCDclear();
    			winner = 0;
    			location = initPlayer();
    			printPlayer(location);
    		}
    	}
    	while (flag2){
    		clearPlayer (location);
    		cursorToLineOne ();
    		writeString (myString3, myString3Length);
    		cursorToLineTwo ();
    		writeString(myString4, myString4Length);
    		if (isP1ButtonPressed (BIT1)) {
    			LCDclear ();
    			flag2 = 0;
    			location = initPlayer ();
    			printPlayer (location);
    		}
    	}
    }
	return 0;
}
// Flag for continuous counting is TAIFG
	#pragma vector=TIMER0_A1_VECTOR
	__interrupt void TIMER0_A1_ISR()
	{
		TACTL &= ~TAIFG;            // clear interrupt flag
		flag ++;
		if (flag == 4) {
			flag2 = 1;
		}
	}
