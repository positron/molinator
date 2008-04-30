#pragma once
#include "Grid.h"
#include "Mole.h"

static const int BLACK_POINTS = -200;
static Color COL_BLACK = Color(Color::black);

class Black_Mole : public Mole
{
	public:
		//we can't pass just Color::black because it would be destroyed and lead to
		//undefined results. Instead pass the address of an already declared black
		Black_Mole( Point pt, int rad )
			: Mole( pt, rad, &COL_BLACK, BLACK_POINTS, &COL_BLACK, new Text( Point(0,0), "" ) )
		{
		}
};
