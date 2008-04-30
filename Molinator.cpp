#include "../../std_lib_facilities.h"
#include "Molinator_Window.h"

/* This file contains the main function that starts the game. Molinator_Window
 * will handle everything once it has been instantiated.  This game compiles
 * with fltk 1.1.7
 */
int main()
{
	if(H112 != 200803L)error("Error: incorrect std_lib_facilities.h version ", H112);

	Molinator_Window *win = new Molinator_Window();
	return 0;
}
