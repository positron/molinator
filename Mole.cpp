#include "../../std_lib_facilities.h"
#include "Mole.h"

Mole::Mole( Point cen )
	: center(cen), radius(DEF_RADIUS)
{
	num_points = point_vals[ randint( 5 ) ];
	m_color = &colors[ randint( 5 ) ];
}

Mole::Mole( Point cen, int rad )
	: center(cen), radius(rad)
{
	num_points = point_vals[ randint( 5 ) ];
	m_color = &colors[ randint( 5 ) ];
}

void Mole::attach( Molinator_Window* w )
{
	cout << sizeof( win ) << " " << sizeof( *win ) << " ";
	cout << "attaching mole" << endl;
	win = w;
//	fl_pie( center.x, center.y, 2*radius, 2*radius, 0, 360 );
	Circle mole( center, radius / 2 );
	mole.set_color( *m_color );
	mole.set_style( Line_style( Line_style::solid, radius / 2 ) );
	win->attach( mole );
}
