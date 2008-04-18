#pragma once
#include "../../GUI.h"

using namespace Graph_lib;

//defaults
static Point DEF_LOCATION = Point(50,50);
static const int DEF_WIDTH = 500;
static const int DEF_HEIGHT = 500;
static string DEF_TITLE = "Molinator";

class Molinator_Window : public Window
{
	public:
		Molinator_Window()
			: Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE )
		{	}

		Molinator_Window( const string& title )
			: Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, title )
		{	}
};
