#pragma once
#include "Grid.h"
#include "Mole.h"

static const int BLACK_POINTS = -200;

class Black_Mole : public Mole
{
	public:
		Black_Mole( Point pt, int rad )
			: Mole( pt, rad, Color::black, BLACK_POINTS )
		{
		}
};
