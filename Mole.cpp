#include "../../std_lib_facilities.h"
#include "Mole.h"

Mole::Mole( int row, int col )
{
	num_points = point_vals[ randint( 5 ) ];
	m_color = &colors[ randint( 5 ) ];
}

void Mole::attach( Molinator_Window* w )
{
	win = w;
	//TODO: draw circle
}
