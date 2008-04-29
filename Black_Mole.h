#pragma once
#include "Grid.h"
#include "Mole.h"

static const int BLACK_POINTS = -200;
static Color COL_BLACK = Color(Color::black);

class Black_Mole : public Mole
{
	public:
		Black_Mole( Point pt, int rad )
			: Mole( pt, rad, &COL_BLACK, BLACK_POINTS, &COL_BLACK, new Text( Point(0,0), "" ) )
		{
		}
};
