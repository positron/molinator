#include "Grid.h"
#include "../../std_lib_facilities.h"

Grid::Grid()
	: grid( 10, vector<Mole*>( 10, NULL ) )
{
}

void Grid::attach( Molinator_Window* w )
{
	win = w;
	//TODO:draw the grid
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
	grid[r][c] = NULL;
	return ret;
}

Mole* Grid::handle_mouse( int x, int y )
{
	int row = x / (WIDTH / ROWS);
	int col = y / (HEIGHT / COLS);
	cout << "click on grid (" << row << ", " << col << ") ";
}
