#include "../../std_lib_facilities.h"
#include "Mole.h"

Mole::Mole( Point cen )
	: center(cen), radius(DEF_RADIUS), circle( cen, DEF_RADIUS / 2 )
{
	num_points = point_vals[ randint( 5 ) ];
	m_color = &colors[ randint( 5 ) ];
}

Mole::Mole( Point cen, int rad )
	: center(cen), radius(rad), circle( cen, rad / 2 )
{
	num_points = point_vals[ randint( 5 ) ];
	m_color = &colors[ randint( 5 ) ];
}

void Mole::attach( Molinator_Window& w )
{
	win = &w;
	cout << sizeof( win ) << " " << sizeof( *win ) << " ";
	cout << "attaching mole" << endl;
//	fl_pie( center.x, center.y, 2*radius, 2*radius, 0, 360 );
	circle.set_color( *m_color );
	circle.set_style( Line_style( Line_style::solid, radius ) );
	win->attach( circle );
	cout << "done attaching circle ";
}
