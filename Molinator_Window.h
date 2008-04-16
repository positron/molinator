#include "../../GUI.h"

using namespace Graph_lib;

		//defaults
		static Point LOCATION = Point(50,50);
		static const int WIDTH = 500;
		static const int HEIGHT = 500;
		static string TITLE = "Molinator";

class Molinator_Window : Window
{
	private:
		bool destroyed;

	public:
		Molinator_Window()
			: Window( LOCATION, WIDTH, HEIGHT, TITLE ),
				destroyed(false)
		{	}

		Molinator_Window( const string& title )
			: Window( LOCATION, WIDTH, HEIGHT, title ),
				destroyed(false)
		{	}

		//Don't do this.  Change it to the handler callback just deletes the stuff.
		void wait_for_destroy()
		{
			while( !destroyed ) Fl::wait();
			Fl::redraw();
		}

	protected:
		void destroy()
		{
			hide();
			destroyed = true;
		}
};
