#include "../../GUI.h"

using namespace Graph_lib;

class Molinator_Window : Window
{
	private:
		bool destroyed;

		//defaults
		static const Point LOCATION(50,50);
		static const int WIDTH = 500;
		static const int HEIGHT = 500;
		static const string TITLE = "Molinator";
	public:
		Molinator_Window()
			: Window( LOCATION, WIDTH, HEIGHT, TITLE ),
				destroyed(false)
		{	}

		Molinator_Window( const string& title )
			: Window( LOCATION, WIDTH, HEIGHT, title ),
				destroyed(false)
		{	}

		void wait_for_destroy()
		{
			while( !destroyed ) Fl::wait();
			Fl::redraw();
		}

	protected:
		void destroy()
		{
			destroyed = true;
		}
}
