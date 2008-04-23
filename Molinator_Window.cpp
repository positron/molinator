#include "../../std_lib_facilities.h"
#include "Molinator_Window.h"
#include "Mole.h"
#include "Grid.h"
#include "timer.h"

Molinator_Window::Molinator_Window()
	: Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE ),
		game(false),
		but_play( Point(50, 50), 60, 20, "Play", cb_play ),
		instruct( Point(60,25), "instruct.jpg" ),
		name_field( Point(200,300), 200, 30, "Enter your name" )
{
	grid = new Grid(); //why doesn't just grid(), work above?
	//TODO: figure out how to make the window so you can't resize it
	init();
}

Molinator_Window::~Molinator_Window()
{
	delete grid;
}

void Molinator_Window::init()
{
	Fl::redraw();
	//add start page stuff to the window
	attach( but_play );
	attach( instruct );
	attach( name_field );
	//TODO: add In_Box and text explaining how to play the game
	//add callback so the window closes when we hit the x button
	callback( *cb_click, this );
	Fl::run();
}

void Molinator_Window::cb_play( Address, Address addr )
{
	static_cast<Molinator_Window*>(addr)->play();
}

//this function is called when the play button has been clicked
void Molinator_Window::play()
{
	//TODO: get username from the In_Box and save it;
	//detach everything on the start screen
	detach( but_play );
	detach( instruct );
	detach( name_field );
	//start the timer function
	Timer::start();
	//start drawing game
	game = true;
	grid->attach( * this );
	grid->add_random_mole();
}

//called when the x button (top right hand corner of window) is hit... I think
void Molinator_Window::cb_click( Fl_Widget*, void* addr )
{
	//notify just in case this causes weird behaviour in Windows
	cout << "Exiting via cb_click\n"; 
	static_cast<Molinator_Window*>(addr)->hide();
}

int Molinator_Window::handle( int event )
{
	//if the event is not a click or if the game isn't running we aren't interested in it
	if( event != FL_RELEASE || !game )
		return Window::handle(event);
	Mole* m = grid->handle_mouse( Fl::event_x(), Fl::event_y() );
	//if we clicked on a Mole, delete it and add another one
	if( m != NULL ) 
	{
		//TODO: add points to score and check if the time is up
		//TODO: if time is up call another function to detach the grid and display high scores
		
		//frees up the memory used by the Mole
		delete m;
		Fl::redraw();
		grid->add_random_mole();
	}
	//let the event propogate down
	return Window::handle(event);
}
