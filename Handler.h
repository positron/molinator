#pragma once
#include "Molinator_Window.h"

/* User_Data is the way data is passed between handlers. (easily modifiable)
 */
struct User_Data
{
	string name;
	int score;
};

/* This Handler base class is intended to "handle" a part of the game. A
 * Handler creates a new initializes a new Molinator_Window, displays it. Then
 * the user has to call run(), which handles the game until it is time for the
 * next Handler to take over. Then it destroys the window returns.
 *
 * Although it may seem useless now this class makes it easier to extend our
 * game by adding levels, etc.
 * Idea: make a "play again" button on the last page that calls the start
 * handler again instead of closing the game.
 *
 * Note: It is up to the main function to call next_handler and start that
 * handler.  This is because if we started another handler from within the
 * current handler pretty soon the call stack would be 500 functions deep
 * because each handler is calling the run method the next handler.  This way
 * there only needs to be one Handler in existance at once if speed or memory
 * is a concern. To emphasize: Once a handler is over it returns, it is up to
 * the user to call next_handler and run the next handler.
 */
class Handler
{
	public:
		Handler();
		Handler( User_Data );

		//start running the handler
		virtual void run() = 0;
		//destroy the window and start the next handler
		//returns null if there's nothign else to do and the game should end
		virtual Handler* next_handler() = 0;

	protected:
		//draw initial objects on screen
		virtual void init() = 0;

	private:
		User_Data data;
		Molinator_Window win;
};
