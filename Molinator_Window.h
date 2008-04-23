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
static const int DEF_HEIGHT = 600;
static string DEF_TITLE = "Molinator";

/* Molinator_Window will manage the game from start to end, all it needs to do
 * is be created.
 */
class Molinator_Window : public Window
{
	public:
		Molinator_Window();
		~Molinator_Window();

		//show the start screen
		void init();
		//override method in Fl_Window to handle events
		int handle( int );

		static void cb_play( Address, Address );
		void play();

		static void cb_click( Fl_Widget*, void* );

	private:
		string name;
		int score;
		
		//set this to true when the game starts, it lets mouse clicks get picked up
		bool game;
		Grid* grid;

		Button but_play;
		Text instruct;
		In_box name_field;
};
