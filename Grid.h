#pragma once
#include "Molinator_Window.h"
#include "Mole.h"
#include "../../GUI.h"

//forward declares
class Molinator_Window;
class Mole;
class Grid;

//consts
static const int ROWS = 10;
static const int COLS = 10;
static const int WIDTH = 600;
static const int HEIGHT = 600;

/* Fltk callbacks only allow one argument to be passed to a callback. For some
 * functions we need more than one piece of data, this struct houses all those
 * variables so we can just pass this argument
 */
struct TO_Data
{
	int row;
	int col;
	Grid* grid;
};

/* This class keeps track of where moles are in the grid. It is kind of
 * useless in the basic version of our game but will be useful when we go
 * for extra credit.
 */
class Grid
{
	public:
		Grid();
		~Grid();

		inline bool is_empty( int, int );
		inline Mole* contains( int, int );
		inline Molinator_Window* window() { return win; }
		bool add( Mole *, int, int );
		Mole* remove( int, int );
		Mole* handle_mouse( int, int );

		void attach( Molinator_Window& w );
		void detach();

		void test()
		{
			cerr << "here in grid test.";
		}

		void start_game();
		void add_random_mole();

		//after a specified time, this function removes the mole and adds a
		//random new one if the user hasn't already clicked on it.
		void timeout_remove_mole( int, int );

		static void cb_add_random_mole( void* );
		static void cb_timeout( void* );
	private:
		Molinator_Window* win;
		Graph_lib::Lines* grid_lines;
		//creates a vector of size 10.  Each of the 10 objects has an initial value
		//of vector<Mole>(10).  To access what is in the vector write grid[i][j]
		vector< vector<Mole*> > grid;
};
