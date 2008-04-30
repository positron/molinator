#include "../../std_lib_facilities.h"
#include "Mole.h"
#include "Grid.h"

/* Important note about drawing circles with Graph_lib:
 * We can not draw filled circles with graph lib, so we have to do a slight
 * hack and just make circles with giant line thicknesses. To draw a circle
 * radius r we have to make a circle with radius r/2 and line thickness r
 */
Mole::Mole( Point cen )
	: center(cen)
{
	Mole_Vals vals = rand_vals();
	num_points = vals.points;
	m_points = new Text( Point( cen.x + vals.text_offset, cen.y+4 ), vals.text_points );
	m_color = vals.col;
	m_txt_col = vals.text_color;
	radius = vals.radius;
	circle = new Circle( center, radius/2 );
}

Mole::Mole( Point cen, int rad )
	: center(cen), radius(rad), circle( new Circle( cen, rad / 2 ) )
{
	Mole_Vals vals = rand_vals();
	num_points = vals.points;
	m_points = new Text( Point( cen.x + vals.text_offset, cen.y+4 ), vals.text_points );
	m_color = vals.col;
	m_txt_col = vals.text_color;
	circle = new Circle( center, radius/2 );
}

//At this point in time, only Black_Mole ever calls this constructor
Mole::Mole( Point cen, int rad, Color* col, int pts, Color* txt_col, Text* txt )
	: center(cen), radius(rad), circle( new Circle( cen, rad / 2 ) ),
		m_color(col), num_points(pts), m_txt_col(txt_col), m_points( txt )
{
}

//preconding: detach has already been called
Mole::~Mole()
{
	delete circle;
	delete m_points;
}

/* Set Molinator_Window and attach the circle and number of points text
 * then draw it on the window.
 */
void Mole::attach( Molinator_Window& w )
{
	win = &w;
//	fl_pie( center.x, center.y, 2*radius, 2*radius, 0, 360 );
	circle->set_color( *m_color );
	circle->set_style( Line_style( Line_style::solid, radius ) );
	m_points->set_color( *m_txt_col );
	m_points->set_font_size( 10 );
	win->attach( *circle );
	win->attach( *m_points );
	//update the window
	Fl::redraw();
}

//detach the circle and points text
void Mole::detach()
{
	if( win != NULL ) win->detach( *circle );
	if( win != NULL ) win->detach( *m_points );
}

//this function returns true if (x,y) is inside the mole (ie the user clicked
//on the mole).
bool Mole::hit_mole( int x, int y )
{
	//use distance formula to calculate distance between click and center of mole
	distance = sqrt( static_cast<double>( (x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) );
	//the user hit the mole if the distance is less than the radius
	return distance < radius;
}

/* Function that every constructor can use to generate random values and their
 * matching colors, offsets, radii, etc.
 */
Mole_Vals Mole::rand_vals()
{
	Mole_Vals val;
	int rand = randint( 5 );
	val.points = point_vals[ rand ];

	stringstream helper;
	helper << val.points;
	val.text_points = helper.str();

	val.radius = WIDTH/ROWS/2 * point_radius_coef[rand];

	val.text_offset = text_offsets[rand];

	rand = randint( 5 );
	val.col = &colors[rand];

	val.text_color = &text_colors[rand];
	return val;
}
