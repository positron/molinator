#include "../../GUI.h"
#include "Molinator_Window.h"

using namespace Graph_lib;

class Start_Window : Molinator_Window
{
		//automatically calls the Molinator_Window default constructor
		Start_Window()
		{
			//initialize and attach text, input field, and button
		}
	private:
		static void cb_start( Address, Address data );

};
