#include <time.h>
#include "../../std_lib_facilities.h"
#include "Molinator_Window.h"
#include "Mole.h"
#include "Grid.h"
#include "scores.h"

Molinator_Window::Molinator_Window()
	:Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE ),

		//Start Screen
		background_top(Point(0,0), "Molinator_start_top.jpg"),
		background_bottom(Point(0,225), "Molinator_start_bottom.jpg"),
		but_play( Point(225,500), 150, 30, "Play the game!", cb_play ),
		name_field( Point(200,450), 200, 30, "" ),
		enter_name( Point(245,445), "Enter Your Name:" ),

		//Game Screen
		clock_text( Point( DEF_WIDTH - 50, DEF_HEIGHT - 1 ), "00" ),
		score_text( Point( 2, DEF_HEIGHT - 1 ), "Score: 0" ),

		//Final Screen
		background_final( Point(0,0), "Molinator_finish.jpg"),
		title( Point(225,225), "High Scores" ),
		stats( Point(240,450), "Statistics" ),
		your_score( Point(150, 500), "" ),//set_label() called in display_scores
		num_moles( Point(150, 525), "" ),
		accuracy( Point(150, 550), "" ),
		precision( Point(150, 575), "" ),
		score1( Point(100,275), "" ),
		score2( Point(100,300), "" ),
		score3( Point(100,325), "" ),
		score4( Point(100,350), "" ),
		score5( Point(100,375), "" ),
		//various variables
		clock(0), score(0), num_clicks(0), moles_whacked(0), sum_dist(0), game(false)
{
	grid = new Grid();
	init();
}

Molinator_Window::~Molinator_Window()
{
	if( grid != NULL ) delete grid;
}

/* Calculates statistics, updates high scores file, and displays the high
 * scores and statistics.
 */
void Molinator_Window::display_scores()
{
	if( num_clicks == 0 ) num_clicks++; //to prevent dividing by 0

	//attach "High Scores" and "Statistics" titles
	background_final.set_fill_color(Color::black);
	attach( background_final );
	title.set_font_size(30);
	title.set_color(Color::white);
	stats.set_font_size(30);
	stats.set_color(Color::white);
	attach( title );
	attach( stats );

	//attach your score
	your_score.set_color(Color::white);
	your_score.set_font(Font::courier_bold);
	your_score.set_font_size(18);
	your_score.set_label( "Your Score: " + int_to_string( score ) + " Points" );

	//attach the number of moles you whacked
	num_moles.set_color(Color::white);
	num_moles.set_font(Font::courier_bold);
	num_moles.set_font_size(18);
	num_moles.set_label( "Moles Whacked: " + int_to_string( moles_whacked ) );

	//attach your accuracy
	accuracy.set_color(Color::white);
	accuracy.set_font(Font::courier_bold);
	accuracy.set_font_size(18);
	//add 0.005 because a conversion to a double to int does not round, it just
	//chops off everything past the decimal. This will make it round correctly
	int acc = static_cast<int>(100*(static_cast<double>(moles_whacked)/num_clicks+0.005));
	accuracy.set_label( "Accuracy: " + int_to_string( acc ) + "%" );

	//attach your precision - average distance from the center of the mole
	precision.set_color(Color::white);
	precision.set_font(Font::courier_bold);
	precision.set_font_size(18);
	precision.set_label( "Precision: " + int_to_string( sum_dist/num_clicks ) + " Pixels" );

	attach( your_score);
	attach( num_moles );
	attach( accuracy );
	attach( precision );
	//add score to high scores list
	Score_IO::add_score( name, score );
	//retrieve top scores
	vector<string> scores = Score_IO::top_scores();

	//Attach the high scores---------------------------------------
	score1.set_font_size(18);
	score1.set_font(Font::courier_bold);
	score1.set_color(Color::white);
	attach( score1 );
	score1.set_label( scores[0] );

	//check if there is a score2 to display
	if( scores.size() < 2 ) return;
	score2.set_font_size(18);
	score2.set_font(Font::courier_bold);
	score2.set_color(Color::white);
	attach( score2 );
	score2.set_label( scores[1] );

	if( scores.size() < 3 ) return;
	score3.set_font_size(18);
	score3.set_font(Font::courier_bold);
	score3.set_color(Color::white);
	attach( score3 );
	score3.set_label( scores[2] );

	if( scores.size() < 4 ) return;
	score4.set_font_size(18);
	score4.set_font(Font::courier_bold);
	score4.set_color(Color::white);
	attach( score4 );
	score4.set_label( scores[3] );

	if( scores.size() < 5 ) return;
	score5.set_font_size(18);
	score5.set_font(Font::courier_bold);
	score5.set_color(Color::white);
	attach( score5 );
	score5.set_label( scores[4] );
}

//Display the start screen
void Molinator_Window::init()
{
	//set background color to black
	color(0);
	//seed random number generator
	srand( time(NULL) );
	Fl::redraw();
	enter_name.set_color( Color::white );
	attach( background_top );
	attach( background_bottom );
	attach( but_play );
	attach( name_field );
	attach( enter_name );
	//add callback so the window closes when we hit the x button
	callback( *cb_click, this );
	Fl::run();
}

//this callback is called when the play button is clicked
void Molinator_Window::cb_play( Address, Address addr )
{
	static_cast<Molinator_Window*>(addr)->play();
}

//this function is called when the play button has been clicked
void Molinator_Window::play()
{
	//set the color of the window back to gray
	color(50);
	name = name_field.get_string();
	//if the user didn't enter a name give them one
	if( name == "" ) name = "Anonymous";
	//detach everything on the start screen
	detach( background_top );
	detach( background_bottom );
	detach( but_play );
	detach( name_field );
	detach( enter_name );
	//start clock - updates every 1.0 seconds
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

/* This function overrides Fl_Window's handl(int) function that is called
 * whenever there is an event.  We are only interested in mouse releases
 * while the game is running, every other even is propogated down to Fl_window
 */
int Molinator_Window::handle( int event )
{
	//if the event is not a click or if the game isn't running we aren't interested in it
	if( event != FL_RELEASE || !game )
		return Window::handle(event); //propogate the event

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

//called at when the game ends
void Molinator_Window::end_game()
{
	//set the cursor back to normal
	cursor( FL_CURSOR_DEFAULT );
	game = false;
	grid->detach();
	display_scores();
}

//called every second to update the clock
void Molinator_Window::update_clock()
{
	clock++;
	string str = int_to_string(clock);
	if( str.length() == 1 ) str = "0" + str;
	clock_text.set_label( str );
	Fl::redraw();
	if( clock >= 50 ) //make the bell beep for the last 10 seconds
		cout << "\a";
	if( clock == 60 ) //your minute is up!
	{ 
		end_game();
		//cancel clock timeout
		Fl::remove_timeout( *cb_update_clock, this );
	}
}

//called when the x button (top right hand corner of window) is hit
void Molinator_Window::cb_click( Fl_Widget*, void* addr )
{
	//hide the window
	static_cast<Molinator_Window*>(addr)->hide();
}

void Molinator_Window::cb_update_clock( void* addr )
{
	//accurately repeat this timeout ever second
	Fl::repeat_timeout( 1.0, *cb_update_clock, addr );
	static_cast<Molinator_Window*>(addr)->update_clock();
}

//aptly named helper function
string Molinator_Window::int_to_string( int i )
{
	//if this is the only way to do this C++ is retarded
	stringstream ss;
	string str;
	ss << i;
	ss >> str;
	return str;
}
