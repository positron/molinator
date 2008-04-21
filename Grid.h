#pragma once
#include "Molinator_Window.h"
#include "Mole.h"

//forward declares
class Molinator_Window;
class Mole;

//consts
static const int ROWS = 10;
static const int COLS = 10;
static const int WIDTH = 600;
static const int HEIGHT = 600;

/* This class keeps track of where moles are in the grid. It is kind of
 * useless in the basic version of our game but will be useful when we go
 * for extra credit.
 */
class Grid
{
	public:
		Grid();
		void attach( Molinator_Window& w );
		inline bool is_empty( int, int );
		inline Mole* contains( int, int );
		bool add( Mole *, int, int );
		Mole* remove( int, int );
		Mole* handle_mouse( int, int );

		void add_random_mole();
	private:
		Molinator_Window* win;
		//creates a vector of size 10.  Each of the 10 objects has an initial value
		//of vector<Mole>(10).  To access what is in the vector write grid[i][j]
		vector< vector<Mole*> > grid;
};
