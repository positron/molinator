#include "Handler.h"
#include "Start_Handler.h"
#include "Game_Handler.h"
#include "../../GUI.h"

Start_Handler::Start_Handler()
{
	init();
}

void Start_Handler::init()
{
	//attach stuff to win
}

void Start_Handler::run()
{
	while( !done ) Fl::wait();
	//check if name matches
	done = true;
	Fl::redraw();
}

void Start_Handler::wait_for_button()
{
}

Handler* Start_Handler::next_handler()
{
//	return Game_Handler( data );
	return 0;
}

