#include "../../std_lib_facilities.h"
#include "Mole.h"
#include "Grid.h"

/* Note about drawing circles with Graph_lib:
 * we can not draw filled circles with graph lib, so we have to do a slight
 * hack and just make circles with giant line thicknesses. To draw a circle
 * radius r we have to make a circle with radius r/2 and line thickness r
 */
Mole::Mole( Point cen )
	: center(cen)
{
	Point m_text;
	int rand = randint( 5 );
	num_points = point_vals[ rand ];
	stringstream helper;
	helper << num_points;
	m_points = new Text( Point(cen.x-9, cen.y+3), helper.str() );
	m_color = &colors[ randint( 5 ) ];
	radius = WIDTH/ROWS/2 * point_radius_coef[rand];
	circle = new Circle( center, radius/2 );
}

Mole::Mole( Point cen, int rad )
	: center(cen), radius(rad), circle( new Circle( cen, rad / 2 ) )
{
	stringstream helper;
	helper << num_points;
	m_points = new Text( Point(cen.x-9, cen.y+3), helper.str() );
	num_points = point_vals[ randint( 5 ) ];
	m_color = &colors[ randint( 5 ) ];
}

Mole::Mole( Point cen, int rad, Color col, int pts )
	: center(cen), radius(rad), circle( new Circle( cen, rad / 2 ) ), m_color(&col), num_points(pts)
{
	stringstream helper;
	helper << num_points;
	m_points = new Text( Point(cen.x-9, cen.y+3), helper.str() );
}

//preconding: detach has already been called
Mole::~Mole()
{
	delete circle;
	delete m_points;
	//TODO: delete text object
}

void Mole::attach( Molinator_Window& w )
{
	win = &w;
//	fl_pie( center.x, center.y, 2*radius, 2*radius, 0, 360 );
	circle->set_color( *m_color );
	circle->set_style( Line_style( Line_style::solid, radius ) );
	m_points->set_color( Color::black );
	m_points->set_font_size( 10 );
	win->attach( *circle );
	win->attach( *m_points );
	//TODO: attach text (number of points)
	Fl::redraw();
}

void Mole::detach()
{
	if( win != NULL ) win->detach( *circle );
	if( win != NULL ) win->detach( *m_points );
	//TODO: detach text
}

//this function returns true if (x,y) is inside the mole (ie the user clicked
//on the mole. 
bool Mole::hit_mole( int x, int y )
{
	//use distance formula to calculate distance between click and center of mole
	distance = sqrt( static_cast<double>( (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) );
//	cout << "dist " << dist << " rad " << radius << "\n";
	return distance < radius;
}
