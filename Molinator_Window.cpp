#include "../../std_lib_facilities.h"
#include "Molinator_Window.h"
#include "Mole.h"
#include "Grid.h"

Molinator_Window::Molinator_Window()
	: Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE ),
		game(false),
		but_play( Point(50, 50), 60, 20, "Play", cb_play )
{
	grid = new Grid(); //why doesn't just grid(), work above?
	//TODO: figure out how to make the window so you can't resize it
	init();
}

void Molinator_Window::init()
{
	Fl::redraw();
	//add start page stuff to the window
	attach( but_play );
	//TODO: add In_Box and text explaining how to play the game
	//add callback so the window closes when we hit the x button
	callback( *cb_click, this );
	Fl::run();
//	while(true) Fl::wait();
}

void Molinator_Window::cb_play( Address, Address addr )
{
	static_cast<Molinator_Window*>(addr)->play();
	cout << "done cb_play()\n";
}

//this function is called when the play button has been clicked
void Molinator_Window::play()
{
	//TODO: get username from the In_Box and save it;
	//detach everything on the start screen
	detach( but_play );
	//start drawing game
	game = true;
	grid->attach( * this );
	grid->add_random_mole();
	cout << "done adding random mole " << endl;
}

//called when the x button (top right hand corner of window) is hit... I think
void Molinator_Window::cb_click( Fl_Widget*, void* addr )
{
	cout << "Exiting via cb_click\n"; //just in case this causes weird behaviour in Windows
	static_cast<Molinator_Window*>(addr)->hide();
}

int Molinator_Window::handle( int event )
{
	//if the event is not a click or if the game isn't running we aren't interested in it
	if( event != FL_RELEASE || !game )
		return Window::handle(event);
	Mole* m = grid->handle_mouse( Fl::event_x(), Fl::event_y() );
	//frees up the memory used by the Mole
//	if( m != NULL ) delete m;
	//let the event propogate down
	return Window::handle(event);
}
