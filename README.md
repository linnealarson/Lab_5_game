Lab_5_game
==========
Objective
The main point of this game was to allow a player to move from the top left corner of the LCD screen to the bottom right corner of the screen. The player moved by using up, down, left, and right button presses, and if they did not press a button within 2 seconds, the game ended and they lost.
Functions
initPlayer(), printPlayer(), clearPlayer(): These functions all dealt with the appearance of the player character on the LCD.
movPlayer(): This function implements the moving of the player across the screen with 4 different inputs.
didPlayerwin(): This function runs while the game is playing and changes if the player moves into the bottom right corner.
Interrupts
Timer0_A1_ISR: This timer waits 2 seconds nad if nothing happens during that time it ends the game. If something does happen, it resets and starts again.
Additional Libraries
Button and LCD libraries
License
Anyone can use and modify this code.
