#include "../../std_lib_facilities.h"
#include "Handler.h"
#include "Start_Handler.h"

/* This file contains the main function and creates scaffolding for the game
 */
int main()
{
	if(H112 != 200803L)error("Error: incorrect std_lib_facilities.h version ", H112);

	Start_Handler start;         //is there any way i can
	Handler *handler = &start;   //do this in one line?
	handler->run();
	//runs the game until next_handler returns null
	while( handler = handler->next_handler() )
	{
		handler->run();
	}
	return 0;
}
