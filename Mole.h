#pragma once
#include "../../Graph.h"
#include "Molinator_Window.h"

using namespace Graph_lib;

//forward declare Molinator_Window
class Molinator_Window;

//random point values - for each point value[i] multiply the moles radius
//by the corresponding coefficient[i]
static const int point_vals[] = { 5, 10, 20, 50, 100 };
static const double point_radius_coef[] = { 1, .9, .75, .55, .4 };
static const double text_offsets[] = { -3, -6, -5, -5, -9 };

//random colors
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

struct Mole_Vals
{
	int points;
	string text_points;
	int text_offset;
	int radius;
	Color* col;
	Color* text_color;
};

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
		Mole_Vals rand_vals();

		Molinator_Window* win;
		//points user gets when "whacked"
		int num_points;
		Color* m_color;  //note, a pointer so we don't have to initalize it in the
		Color* m_txt_col;//constructor, because there is not Color() constructor

		Point center;
		int radius;
		Circle* circle;
		Text* m_points;

		//for stats
		int distance;

		static const int DEF_RADIUS = 30;
};
