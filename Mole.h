#pragma once
#include "../../Graph.h"
#include "Molinator_Window.h"

using namespace Graph_lib;

//forward declare Molinator_Window
class Molinator_Window;

static const int point_vals[] = { 5, 10, 20, 50, 100 };
static Color colors[] = { 
	Color(Color::red), 
	Color(Color::blue), 
	Color(Color::green), 
	Color(Color::yellow), 
	Color(Color::magenta)
	};

/* This class
 */
class Mole
{
	public:
		Mole( Point );
		Mole( Point, int );
		Mole( Point, int, Color, int );
		
		inline int points() { return num_points; }
		inline Color color() { return *m_color; }

		bool hit_mole( int, int );

		void attach( Molinator_Window& w );
		void detach();
	private:
		Molinator_Window* win;
		//points user gets when "whacked"
		int num_points;
		Color* m_color; //note, a pointer so we don't have to initalize it in the
										//constructor, because there is not Color() constructor
		Point center;
		int radius;
		Circle circle;

		static const int DEF_RADIUS = 30;
};
