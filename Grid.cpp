#include "Grid.h"
#include "../../std_lib_facilities.h"

Grid::Grid()
	: grid( 10, vector<Mole*>( 10, NULL ) )
{
}

Grid::~Grid()
{
	//delete any Moles left in the grid
	Mole* m;
	for( int r = 0; r < ROWS; r++ )
	{
		for( int c = 0; c < COLS; c++ )
		{
			m = grid[r][c];
			if( m != NULL ) delete m;
		}
	}
}

void Grid::attach( Molinator_Window& w )
{
	win = &w;
	cout << sizeof( win ) << " " << sizeof( *win ) << " ";
	cout << "attaching grid to window" << endl;
	//TODO:draw the grid
}

void Grid::detach()
{
	//TODO: detach the grid
}

bool Grid::is_empty( int row, int col )
{
	return ( contains( row, col ) == NULL ) ? true : false;
}

Mole* Grid::contains( int row, int col )
{
	return grid[row][col];
}

bool Grid::add( Mole* m, int r, int c )
{
	if( !is_empty( r, c ) ) return false;
	grid[r][c] = m;
	return true;
}

//returns the Mole in the grid, or NULL if it is empty
Mole* Grid::remove( int r, int c )
{
	//just returns null if it is empty
	Mole* ret = grid[r][c];
	if( ret != NULL ) ret->detach();
	grid[r][c] = NULL;
	return ret;
}

Mole* Grid::handle_mouse( int x, int y )
{
	int row = x / (WIDTH / ROWS);
	int col = y / (HEIGHT / COLS);
	cout << "click on grid (" << row << ", " << col << ") ";
	return remove( row, col );
}

void Grid::add_random_mole()
{
	int row, col;
	do
	{
		row = randint( ROWS );
		col = randint( COLS );
	} while ( !is_empty( row, col ) );
	Point center( (row+0.5)*WIDTH/ROWS, (col+0.5)*HEIGHT/COLS );
	//why do we have to do this?  We have to make a new Mole.  if we just make a temp one the program segfaults...
	Mole* m = new Mole( center, WIDTH/ROWS/2 - 4 );
	m->attach( * win );
	grid[row][col] = m;
//	grid[row][col]->attach( * win );
}
