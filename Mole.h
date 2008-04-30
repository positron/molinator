#pragma once
#include "../../Graph.h"
#include "Molinator_Window.h"

using namespace Graph_lib;

//forward declare Molinator_Window
class Molinator_Window;

/* With a single random int we can get a random point_val, along with the
 * corresponding radius coefficient (higher points have smaller radii, which
 * is why we multiply the radius for a 100 pt mole by .4) and text offset
 * (which tells us where to put the text object displaying how many points
 * the mole is worth
 */
static const int point_vals[] = { 5, 10, 20, 50, 100 };
static const double point_radius_coef[] = { 1, .9, .75, .55, .4 };
static const double text_offsets[] = { -3, -6, -5, -5, -9 };

/* The colors and text colors work similarly to the arrays above
 */
static Color colors[] = { 
	Color(Color::red), 
	Color(Color::blue), 
	Color(Color::green), 
	Color(Color::yellow), 
	Color(Color::magenta)
};

//text colors to match random background colors above
static Color text_colors[] = {
	Color(Color::white),
	Color(Color::white),
	Color(Color::black),
	Color(Color::black),
	Color(Color::black)
};

/* This struct contains all the properties of a mole that can be randomly set.
 * Since only two values are truely random, the points and the color, a
 * function populates Mole_Vals with the two random variables and their
 * corresponding variables (offsets, radius, etc.)
 */
struct Mole_Vals
{
	int points;
	string text_points;
	int text_offset;
	int radius;
	Color* col;
	Color* text_color;
};

/* In charge of drawing a mole on a window and detaching itself if it is hit.
 */
class Mole
{
	public:
		Mole( Point );
		Mole( Point, int );
		Mole( Point, int, Color*, int, Color*, Text* );
		~Mole();
		
		inline int points() { return num_points; }
		inline Color color() { return *m_color; }
		inline int dist() { return distance; }

		bool hit_mole( int, int );

		void attach( Molinator_Window& w );
		void detach();
	private:
		Mole_Vals rand_vals();//returns a randomly populated Mole_Vals

		Molinator_Window* win;

		int num_points; //points user gets when whacked
		Color* m_color;  //note, a pointer so we don't have to initalize it in the
		Color* m_txt_col;//constructor, because there is no default Color() constructor

		Point center;
		int radius;
		Circle* circle;
		Text* m_points;

		//for stats
		int distance;

		static const int DEF_RADIUS = 30;
};
