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
static const int DEF_HEIGHT = 620; //20 extra pixels for clock and scores
static string DEF_TITLE = "Molinator";

/* Molinator_Window will manage the game from start to end, all it needs to do
 * is be created. When it is created init() is called, which displays the start
 * screen. When the play button is clicked a callback calls play(), which
 * detaches start screen objects and starts the game. After 60 seconds is up
 * end_game() is called, which detaches game objects and calls display_scores(),
 * which displays the final results screen with the high scores.
 */
class Molinator_Window : public Window
{
	public:
		Molinator_Window();
		~Molinator_Window();

		inline bool get_game() { return game; }
		void init(); //show start screen
		//override method in Fl_Window to handle events
		int handle( int );

		void display_scores();
		void end_game();
		inline void play();          //We can inline these functions even though they
		inline void update_clock();  //are big because they are called from callbacks

		//callbacks
		static void cb_play( Address, Address );
		static void cb_click( Fl_Widget*, void* );
		static void cb_update_clock( void* );

	private:
		string int_to_string( int );//descriptively named helper function

		string name;
		int score;
		int clock;
		
		//set this to true when the game starts, it lets mouse clicks get picked up
		//and controls callbacks
		bool game;
		Grid* grid;

		//stats - accuracy is #moles destroyed / #clicks
		//        precision is sum of distance / #clicks
		int moles_whacked; //number of moles killed
		int sum_dist;      //sum of distance between click and center of mole
		int num_clicks;    //number of clicks during the 60 sec game

		//start screen objects
		Image background_top;
		Image background_bottom;
		Text enter_name;
		Button but_play;
		In_box name_field;

		//game objects
		Text score_text;
		Text clock_text;

		//results screen objects
		Image background_final;
		Text title;
		Text stats;
		Text your_score;
		Text num_moles;
		Text precision;
		Text accuracy;
		Text score1;
		Text score2;
		Text score3;
		Text score4;
		Text score5;
};
