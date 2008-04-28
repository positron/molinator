#pragma once
#include <FL/Fl_Widget.H>
#include "../../GUI.h"
#include "../../Graph.h"
#include "Grid.h"

using namespace Graph_lib;

//forward declare Grid
class Grid;

//defaults
static Point DEF_LOCATION = Point(50,50);
static const int DEF_WIDTH = 600;
static const int DEF_HEIGHT = 620;
static string DEF_TITLE = "Molinator";

//global game over variable
extern bool glob_game_over;

/* Molinator_Window will manage the game from start to end, all it needs to do
 * is be created.
 */
class Molinator_Window : public Window
{
	public:
		Molinator_Window();
		~Molinator_Window();

		inline bool get_game() { return game; }
		//show the start screen
		void init();
		//override method in Fl_Window to handle events
		int handle( int );

		void display_scores();
		void end_game();
		inline void play();          //We can inline these functions even though they
		inline void update_clock();  //are big because they are called from callbacks

		static void cb_play( Address, Address );
		static void cb_click( Fl_Widget*, void* );
		static void cb_update_clock( void* );

	private:
		string int_to_string( int );

		string name;
		int score;
		int clock;
		
		//set this to true when the game starts, it lets mouse clicks get picked up
		bool game;
		Grid* grid;

		//stats - accuracy is #moles destroyed / #clicks
		//        precision is sum of distance / #clicks
		int moles_whacked; //number of moles killed
		int sum_dist;      //sum of distance between click and center of mole
		int num_clicks;    //number of clicks during the 60 sec game

		Text score_text;
		Text clock_text;
		Button but_play;
		Image instruct;
		In_box name_field;
};
