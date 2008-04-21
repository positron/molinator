#include "../../std_lib_facilities.h"
#include "Molinator_Window.h"

/* This file contains the main function and creates scaffolding for the game
 */
int main()
{
	if(H112 != 200803L)error("Error: incorrect std_lib_facilities.h version ", H112);

	Molinator_Window *win = new Molinator_Window();
//Molinator_Window win(); //why does this not work?
	return 0;
}
