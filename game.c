/*
 * game.c
 * Author: Linnea Larson
 * Version 1 - Created initially from Capt Branchflower's shell
 * Functions to implement various functions to play cursor game
 */

#include <msp430g2553.h>
#include "game.h"
#include "LCD/Lab4_LCD.h"
#include "buttons/button.h"

unsigned char initPlayer()
{
	return 0x80;
}

void printPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte(' ');
}

unsigned char movePlayer(unsigned char player, unsigned char direction)
{
	switch (direction) {
		case UP:
			clearPlayer(player);
			player &= ~ROW_MASK;
			printPlayer(player);
		break;
		case DOWN:
			clearPlayer(player);
			player |= ROW_MASK;
			printPlayer(player);
		break;
		case RIGHT:
			clearPlayer(player);
			player =player + 1;
			if (player == 0x88|player == 0xC8) {
				player = player - 1;
			}
			printPlayer (player);
			waitForP1ButtonRelease (BIT3);
		break;
		case LEFT:
			clearPlayer (player);
			player = player - 1;
			if (player == 0x7F|player == 0xBF) {
				player = player + 1;
			}
			printPlayer (player);
			waitForP1ButtonRelease (BIT4);
		break;

		//
		// update player position based on direction of movement
		//
	}

	return player;
}

char didPlayerWin(unsigned char player)
{
	return player == 0xC7;
}
