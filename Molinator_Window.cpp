#include "../../std_lib_facilities.h"
#include "Molinator_Window.h"
#include "Mole.h"
#include "Grid.h"
#include "timer.h"

Molinator_Window::Molinator_Window()
	: Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE ),
		game(false),
		but_play( Point(200, 400), 150, 20, "Play the game!", cb_play ),
		instruct( Point(60,25), "instruct.jpg" ),
		name_field( Point(200,300), 200, 30, "Enter your name" ),
		clock_text( Point( DEF_WIDTH - 50, DEF_HEIGHT - 1 ), "00" ),
		score_text( Point( 2, DEF_HEIGHT - 1 ), "Score: 0" ),
		clock(0), score(0), num_clicks(0), moles_whacked(0), sum_dist(0)
{
	grid = new Grid(); //why doesn't just grid(), work above?
	//TODO: figure out how to make the window so you can't resize it
	init();
}

Molinator_Window::~Molinator_Window()
{
	if( grid != NULL ) delete grid;
}

void Molinator_Window::display_scores()
{
	//TODO: display top scores and game statistics: your score, accuracy, and precision
}

void Molinator_Window::init()
{
	Fl::redraw();
	//add start page stuff to the window
	attach( but_play );
	attach( instruct );
	attach( name_field );
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
	//TODO? if( ask("do you really be anonymous?" )
	//detach everything on the start screen
	detach( but_play );
	detach( instruct );
	detach( name_field );
	//start clock
	Fl::add_timeout( 1.0, * cb_update_clock, this );
	//set the cursor to be a cross
	cursor( FL_CURSOR_CROSS );
	//draw clock and score
	clock_text.set_font_size( 20 );
	score_text.set_font_size( 20 );
	attach( clock_text );
	attach( score_text );
	Fl::redraw();
	//start drawing game
	game = true;
	grid->attach( * this );
	grid->start_game();
}

int Molinator_Window::handle( int event )
{
	//if the event is not a click or if the game isn't running we aren't interested in it
	if( event != FL_RELEASE || !game )
		return Window::handle(event);
	Mole* m = grid->handle_mouse( Fl::event_x(), Fl::event_y() );
	num_clicks++;
	//if we clicked on a Mole, delete it and add another one
	if( m != NULL ) 
	{
		score += m->points();
		moles_whacked++;
		sum_dist += m->dist();
		//update score_text
		score_text.set_label( "Score: " + int_to_string( score ) );
		//don't need Fl::redraw because add_random_mole() will do it for us

		//frees up the memory used by the Mole
		delete m;
		//add a new mole to replace the lost one
		grid->add_random_mole();
	}
	//let the event propogate down
	return Window::handle(event);
}

void Molinator_Window::end_game()
{
	cursor( FL_CURSOR_DEFAULT );
	//stupid hack because our cb code has issues
	game = false;
	grid->detach();
//	delete grid;
//	grid = NULL;
//what?? even though we just deleted grid we can still call the method test and it couts stuff..??
//	grid->test(); //This is dumb...
	display_scores();
	//TODO: don't just cout this, display it on the final screen
	if( num_clicks == 0 ) num_clicks++; //to prevent floating point exception
	cout << "\n-----FINAL STATS------\n";
	cout << "accuracy: " << static_cast<int>(100*(static_cast<double>(moles_whacked)/num_clicks+0.005)) << "%\n";
	cout << "precision: " << (sum_dist/num_clicks) << "px\n";
	cout << "score: " << score << "\n";
}

void Molinator_Window::update_clock()
{
	clock++;
	string str = int_to_string(clock);
	if( str.length() == 1 ) str = "0" + str;
	clock_text.set_label( str );
	Fl::redraw();
	if( clock == 60 )
	{ 
		end_game();
		//cancel clock timeout
		Fl::remove_timeout( *cb_update_clock, this );
	}
}

//called when the x button (top right hand corner of window) is hit... I think
void Molinator_Window::cb_click( Fl_Widget*, void* addr )
{
	static_cast<Molinator_Window*>(addr)->hide();
}

void Molinator_Window::cb_update_clock( void* addr )
{
	Fl::repeat_timeout( 1.0, *cb_update_clock, addr );
	static_cast<Molinator_Window*>(addr)->update_clock();
}

//helper function
string Molinator_Window::int_to_string( int i )
{
	//if this is the only way to do this C++ is retarded
	stringstream ss;
	string str;
	ss << i;
	ss >> str;
	return str;
}
