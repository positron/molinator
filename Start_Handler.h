#pragma once
#include "../../GUI.h"
#include "Handler.h"

using namespace Graph_lib;

class Start_Handler : public Handler
{
	public:
		Start_Handler();
		Start_Handler( User_Data ){	}

		//TODO: is keyword virtual needed? or is it at least good programming style
		//in case someone needs to extend Start_Handler?
		void run();
		Handler* next_handler();

		void wait_for_button();

	protected:
		void init();
	private:
		bool done;
		//Address is just a void pointer
		static void cb_play( Address, Address );

};
