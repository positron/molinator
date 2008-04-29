#include "Grid.h"
#include "Black_Mole.h"
#include "../../std_lib_facilities.h"

Grid::Grid()
	: grid( 10, vector<Mole*>( 10, NULL ) )
{
}

//precondition: detach has already been called
Grid::~Grid()
{
	//delete any Moles left in the grid
/*	Mole* m;
	for( int r = 0; r < ROWS; r++ )
	{
		for( int c = 0; c < COLS; c++ )
		{
			m = grid[r][c];
			if( m != NULL ) delete m;
		}
	}
	*/
//	if( grid_lines != NULL ) 
		delete grid_lines;
}

void Grid::attach( Molinator_Window& w )
{
	win = &w;
	//draw the grid
	int x_size = WIDTH;
	int y_size = HEIGHT;
	int x_grid = HEIGHT/ROWS;
	int y_grid = WIDTH/COLS;
	
	grid_lines = new Lines();
	for (int x=x_grid;x<x_size;x+=x_grid)
		grid_lines->add(Point(x,0),Point(x,y_size));
	//y<=y_size so it draws the bottom line
	for (int y=y_grid;y<=y_size;y+=y_grid)
		grid_lines->add(Point(0,y),Point(x_size,y));
	win->attach(*grid_lines);
}

void Grid::detach()
{
	//detach and delete any Moles left in the grid
	Mole* m;
	for( int r = 0; r < ROWS; r++ )
	{
		for( int c = 0; c < COLS; c++ )
		{
			m = grid[r][c];
			if( m != NULL )
			{
				m->detach();
				grid[r][c] = NULL;
				delete m;
			}
		}
	}
	if( win != NULL && grid_lines != NULL ) win->detach( *grid_lines );
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
	//check for range errors just in case (eg resized window)
	if( row < 0 || row > 9 || col < 0 || col > 9 ) return NULL;
	Mole* m = contains( row, col );
	if( m == NULL ) return NULL;
  //only remove the mole if the user actually hit the mole, not if he just
	//clicked in the grid
	if( m->hit_mole( x, y ) )
		return remove( row, col );
	return NULL;
}

void Grid::add_random_mole()
{
	//get row and col that isn't already occupied
	int row, col;
	do
	{
		row = randint( ROWS );
		col = randint( COLS );
	} while ( !is_empty( row, col ) );
	Point center( (row+0.5)*WIDTH/ROWS, (col+0.5)*HEIGHT/COLS );
	int rad = WIDTH/ROWS/2;
	Mole* m;
	//randomly add black moles 1 in 10 times
	if( randint(10) == 0 )
		m = new Black_Mole( center, rad );
	else
		m = new Mole( center );
	m->attach( * win );
	grid[row][col] = m;
	//add a callback for a random time interval between 1.6 and 2.6 seconds
	double time = randint( 11 ) / 10.0 + 1.6;
	//we have to create a new to data because it will disappear with scope
	TO_Data* dat = new TO_Data();
	dat->row = row;
	dat->col = col;
	dat->grid = this;
	Fl::add_timeout( time, * cb_timeout, dat );
}

void Grid::timeout_remove_mole( int row, int col )
{
	//if the mole is already gone, do nothing
	if( is_empty( row, col ) ) return;
	//otherwise remove the mole and add another random one
	remove( row, col );
	add_random_mole();
}

void Grid::start_game()
{
	add_random_mole();
	Fl::add_timeout( 1.0, * cb_add_random_mole, this );
	Fl::add_timeout( 2.0, * cb_add_random_mole, this );
	Fl::add_timeout( 20.0, * cb_add_random_mole, this );
	//add a bunch of moles at the end of the game, heh heh
	Fl::add_timeout( 45.0, * cb_add_random_mole, this );
	Fl::add_timeout( 47.0, * cb_add_random_mole, this );
	Fl::add_timeout( 50.0, * cb_add_random_mole, this );
}

void Grid::cb_add_random_mole( void* addr )
{
	Grid* g = static_cast<Grid*>(addr);
	if( g == NULL ) return;
	if( !g->window()->get_game() ) return;
	g->add_random_mole();
}

void Grid::cb_timeout( void* addr )
{
	if( addr == NULL ) return;
	TO_Data* dat = static_cast<TO_Data*>(addr);
	Grid* g = dat->grid;
	if( g == NULL ) return;
	if( static_cast<TO_Data*>(addr)->grid == NULL ) return;
	if( !g->window()->get_game() ) return;
	//annoying bug: check if the grid has been removed in the intervening time
	g->timeout_remove_mole( dat->row, dat->col );
	//since we had to make a new TO_Data we have to free up it's memory
	delete addr;
}
