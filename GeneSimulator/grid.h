#pragma once

#include "population.h"

#include "globals.h"

class Grid {
private:
	uint16_t* grid;
	Population population;

public:
	Grid(Population &population);
};